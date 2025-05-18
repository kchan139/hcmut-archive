import argparse
import time
import config
from tracker import Tracker
from node import Node
import logging
import os

# Configure Logging
logging.basicConfig(level=config.LOGGING_LEVEL, format="%(asctime)s [%(levelname)s] %(message)s")

def start_tracker():
    tracker = Tracker(config.TRACKER_HOST, config.TRACKER_PORT)  # Bind to all interfaces for multi-host compatibility
    tracker.start()

def start_node(node_id, port, tracker_host, tracker_port, action=None, file_name=None):
    tracker_address = (tracker_host, tracker_port)
    node = Node(node_id, port, tracker_address)
    logging.info(f"Starting {action} on Node {node_id} (port {port}), tracker at {tracker_host}:{tracker_port}")
    if action == "announce":
        if file_name is None:
            raise ValueError("File name must be provided for announcing.")
        node.contact_tracker(file_name)  # Announce the file
        node.listen_for_peers()  # Listen for requests
    elif action == "request":
        if file_name is None:
            raise ValueError("File name must be provided for requesting.")
        time.sleep(2)  # Wait for the announcement to complete
        peers = [{"peer_id": "node_1", "ip": tracker_host, "port": 5001}]
        node.request_file(file_name, peers[0])

def setup_environment(file_name):
    """Set up directories and test file for the file-sharing environment."""
    os.makedirs(config.EXAMPLE_DIR, exist_ok=True)
    os.makedirs(config.DOWNLOAD_DIR, exist_ok=True)
    test_file_path = os.path.join(config.EXAMPLE_DIR, file_name)
    if not os.path.exists(test_file_path):
        with open(test_file_path, "w") as f:
            f.write(f"This is a test file named {file_name} for P2P file sharing.")

def main():
    parser = argparse.ArgumentParser(description="P2P File Sharing Application")
    parser.add_argument("--role", choices=["tracker", "announce", "request"], required=True, help="Role: tracker, announce, or request")
    parser.add_argument("--node_id", type=int, help="Node ID (for announce or request)")
    parser.add_argument("--port", type=int,default=config.TRACKER_PORT, required=True, help="Port to listen on")
    parser.add_argument("--tracker_host", type=str, default=config.TRACKER_HOST, help="Tracker host address (for announce or request)")
    parser.add_argument("--tracker_port", type=int, default=config.TRACKER_PORT, help="Tracker port (for announce or request)")
    parser.add_argument("--file_name", type=str, help="File name to announce or request")
    args = parser.parse_args()

    if args.role == "tracker":
        start_tracker()
    elif args.role in ["announce", "request"]:
        if not args.node_id or not args.file_name:
            parser.error("--node_id and --file_name are required for announce and request roles")
        if args.role == "announce":
            setup_environment(args.file_name)  # Set up the example file
        start_node(args.node_id, args.port, args.tracker_host, args.tracker_port, action=args.role, file_name=args.file_name)

if __name__ == "__main__":
    main()
