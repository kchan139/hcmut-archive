import threading
import time
import os
from tracker import Tracker
from node import Node
import config
import logging

# Configure Logging
logging.basicConfig(level=config.LOGGING_LEVEL, format="%(asctime)s [%(levelname)s] %(message)s")

# Helper function to start the tracker
def start_tracker():
    tracker = Tracker(config.TRACKER_HOST, config.TRACKER_PORT)
    tracker.start()

# Helper function to start a node
def start_node(node_id, port, tracker_address, action=None, file_name=None):
    node = Node(node_id, port, tracker_address)
    if action == "announce":
        node.run()  # Announces and listens for requests
    elif action == "request":
        time.sleep(2)  # Wait for the announcement to complete
        peers = [{"peer_id": "node_1", "ip": config.TRACKER_HOST, "port": 5001}]
        node.request_file(file_name, peers[0])

def verify_file_transfer(file_name):
    """Verify if the file was successfully transferred."""
    original_file = os.path.join(config.EXAMPLE_DIR, file_name)
    downloaded_file = os.path.join(config.DOWNLOAD_DIR, file_name)
    if os.path.exists(downloaded_file):
        with open(original_file, "rb") as orig, open(downloaded_file, "rb") as down:
            if orig.read() == down.read():
                logging.info(f"File transfer verification passed for {file_name}")
            else:
                logging.error(f"File content mismatch for {file_name}")
    else:
        logging.error(f"File {file_name} not found in downloads.")


def setup_environment():
    """Set up directories and test file for the file-sharing environment."""
    os.makedirs(config.EXAMPLE_DIR, exist_ok=True)
    os.makedirs(config.DOWNLOAD_DIR, exist_ok=True)
    
    test_file_path = os.path.join(config.EXAMPLE_DIR, "test.txt")
    logging.info(f"Test file created at {test_file_path}")

def main():
    file_name = "1.jpeg"
    setup_environment()

    # Start the tracker in a separate thread
    tracker_thread = threading.Thread(target=start_tracker, daemon=True)
    tracker_thread.start()
    time.sleep(1)  # Give the tracker time to start

    # Start Node 1 (announces the file)
    node_1_thread = threading.Thread(
        target=start_node,
        args=(1, 5001, (config.TRACKER_HOST, config.TRACKER_PORT), "announce"),
        daemon=True,
    )
    node_1_thread.start()

    # Start Node 2 (requests the file from Node 1)
    node_2_thread = threading.Thread(
        target=start_node,
        args=(2, 5002, (config.TRACKER_HOST, config.TRACKER_PORT), "request", file_name),
        daemon=True,
    )
    node_2_thread.start()

    # Wait for the nodes to complete their actions
    time.sleep(5)

    # Verify the file transfer
    verify_file_transfer(file_name)

if __name__ == "__main__":
    main()
