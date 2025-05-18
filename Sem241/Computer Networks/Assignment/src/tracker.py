import socket
import threading
import json
import logging
import config

# Logging Configuration
logging.basicConfig(level=config.LOGGING_LEVEL, format="%(asctime)s [%(levelname)s] %(message)s")

class Tracker:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.files = {}  # Tracks files and their associated peers

    def start(self):
        logging.info(f"Tracker is running on {self.host}:{self.port}")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
            server_socket.bind((self.host, self.port))
            server_socket.listen(config.MAX_CONNECTIONS)
            while True:
                conn, addr = server_socket.accept()
                threading.Thread(target=self.handle_peer, args=(conn, addr)).start()

    def handle_peer(self, conn, addr):
        logging.info(f"Connected to peer at {addr}")
        try:
            data = conn.recv(1024).decode('utf-8')
            if not data:
                return
            message = json.loads(data)
            if message["type"] == "announce":
                self.handle_announce(message, addr)
                response = {"status": "success", "message": "Announce received"}
                conn.sendall(json.dumps(response).encode('utf-8'))
            elif message["type"] == "request":
                self.handle_request(conn, message)
            else:
                response = {"status": "failure", "message": "Unknown request type"}
                conn.sendall(json.dumps(response).encode('utf-8'))
        except Exception as e:
            logging.error(f"Error handling peer at {addr}: {e}")
        finally:
            conn.close()

    def handle_announce(self, message, addr):
        peer_info = {"peer_id": message["peer_id"], "ip": addr[0], "port": message["port"]}
        for file in message["files"]:
            if file["file_name"] not in self.files:
                self.files[file["file_name"]] = []
            self.files[file["file_name"]].append(peer_info)
        logging.info(f"Announce received from {message['peer_id']}: {message['files']}")

    def handle_request(self, conn, message):
        """Handle file requests from peers."""
        file_name = message["file_name"]
        if file_name in self.files:
            response = {"status": "success", "peers": self.files[file_name]}
        else:
            response = {"status": "failure", "message": f"File {file_name} not found"}
        conn.sendall(json.dumps(response).encode('utf-8'))



if __name__ == "__main__":
    tracker = Tracker(config.TRACKER_HOST, config.TRACKER_PORT)
    tracker.start()
