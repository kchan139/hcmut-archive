# config.py

# Tracker Configuration
TRACKER_HOST = '0.0.0.0'  # Default IP address of the tracker
TRACKER_PORT = 8080         # Default port for the tracker to listen on
TRACKER_TIMEOUT = 30        # Timeout (in seconds) for tracker connections

# Node Configuration
NODE_PORT_RANGE = (5000, 5100)  # Range of ports available for nodes
NODE_TIMEOUT = 30               # Timeout (in seconds) for peer connections
MAX_CONNECTIONS = 10            # Maximum number of simultaneous peer connections

# File Sharing Configuration
PIECE_SIZE = 512 * 1024         # Size of each file chunk in bytes (512 KB)
EXAMPLE_DIR = './data/example'  # Directory to store metadata files
DOWNLOAD_DIR = './data/downloads' # Directory for downloaded files

# Protocol Configuration
PROTOCOL_VERSION = '1.0'        # Version of the protocol
MAX_RETRY_ATTEMPTS = 3          # Maximum retry attempts for failed connections

# Logging Configuration
LOGGING_LEVEL = 'DEBUG'         # Logging level (DEBUG, INFO, WARNING, ERROR, CRITICAL)
LOG_FILE = './logs/application.log'  # Path to the log file
