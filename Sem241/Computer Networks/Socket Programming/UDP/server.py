from socket import *

# Specify server port
SERVER_PORT = 12000

# Create UDP socket
server_socket = socket(AF_INET, SOCK_DGRAM)

try:
    # Bind socket to local port number 12000
    server_socket.bind(('', SERVER_PORT))
    # Indicate that the server is ready to receive messages
    print("The server is ready to receive!")

    # Continuously listen for incoming messages
    while True:
        # Receive a message and the address of the client
        message, client_address = server_socket.recvfrom(2048)
        # Decode the message to uppercase
        modified_message = message.decode().upper()
        # Send the modified message back to the client
        server_socket.sendto(modified_message.encode(), client_address)

except Exception as e:
    # Print any errors that occur during execution
    print(f"Error: {e}")