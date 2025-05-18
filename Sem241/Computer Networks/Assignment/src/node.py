import os
import socket
import threading
import json
import logging
import config

# Logging Configuration
logging.basicConfig(
    level=config.LOGGING_LEVEL, 
    format="%(asctime)s [%(levelname)s] %(message)s"
)

class Node:
    def __init__(self, node_id, port, tracker_address):
        self.node_id = node_id
        self.port = port
        self.tracker_address = tracker_address

    def run(self, file_name=None):
        """Announce a file and listen for peer requests."""
        logging.info(f"Node {self.node_id} is running on port {self.port}")
        self.contact_tracker(file_name)
        self.listen_for_peers()

    def contact_tracker(self, file_name):
        """Announce available files to the tracker."""
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
                client_socket.connect(self.tracker_address)
                files = [{"file_name": file_name, "file_size": os.path.getsize(os.path.join(config.EXAMPLE_DIR, file_name))}]
                message = {
                    "type": "announce",
                    "peer_id": f"node_{self.node_id}",
                    "port": self.port,
                    "files": files,
                }
                client_socket.sendall(json.dumps(message).encode('utf-8'))
                response = client_socket.recv(1024).decode('utf-8')
                logging.info(f"Node {self.node_id} received tracker response: {response}")
        except Exception as e:
            logging.error(f"Node {self.node_id} failed to contact tracker: {e}")

    def listen_for_peers(self):
        """Listen for requests from other peers."""
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
                server_socket.bind(('', self.port))
                server_socket.listen(config.MAX_CONNECTIONS)
                logging.info(f"Node {self.node_id} listening on port {self.port}")
                while True:
                    conn, addr = server_socket.accept()
                    threading.Thread(target=self.handle_peer_request, args=(conn, addr)).start()
        except Exception as e:
            logging.error(f"Node {self.node_id} failed to listen for peers: {e}")

    def handle_peer_request(self, conn, addr):
        """Handle file requests from peers."""
        try:
            data = conn.recv(1024).decode('utf-8')
            if not data:
                return
            message = json.loads(data)
            if message["type"] == "request":
                file_name = message["file_name"]
                file_path = os.path.join(config.EXAMPLE_DIR, file_name)
                if os.path.exists(file_path):
                    with open(file_path, "rb") as file:  # Open in binary mode
                        file_data = file.read()
                        conn.sendall(file_data)
                        logging.info(f"Node {self.node_id} sent file {file_name} to peer at {addr}")
                else:
                    response = {"status": "failure", "message": f"File {file_name} not found"}
                    conn.sendall(json.dumps(response).encode('utf-8'))
        except Exception as e:
            logging.error(f"Node {self.node_id} failed to handle peer request: {e}")
        finally:
            conn.close()

    def request_file(self, file_name, peer):
        """Request a file from another peer."""
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
                client_socket.connect((peer["ip"], peer["port"]))
                message = {"type": "request", "file_name": file_name}
                client_socket.sendall(json.dumps(message).encode('utf-8'))
                file_data = b""  # Use binary data
                while True:  # Read all chunks
                    chunk = client_socket.recv(config.PIECE_SIZE)
                    if not chunk:
                        break
                    file_data += chunk
                file_path = os.path.join(config.DOWNLOAD_DIR, file_name)
                with open(file_path, "wb") as file:  # Write in binary mode
                    file.write(file_data)
                logging.info(f"Node {self.node_id} successfully downloaded {file_name}")
        except Exception as e:
            logging.error(f"Node {self.node_id} failed to download {file_name}: {e}")


    def get_available_files(self):
        """Scan the directory for available files."""
        files = []
        for file_name in os.listdir(config.EXAMPLE_DIR):
            file_path = os.path.join(config.EXAMPLE_DIR, file_name)
            if os.path.isfile(file_path):
                files.append({"file_name": file_name, "file_size": os.path.getsize(file_path)})
        return files