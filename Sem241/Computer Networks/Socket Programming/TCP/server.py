from socket import *

# Define the port number for the server
SERVER_PORT = 12000

# Create a TCP welcoming socket
server_socket = socket(AF_INET, SOCK_STREAM)

try:
    # Bind the socket to the specified port
    server_socket.bind(('', SERVER_PORT))

    # Listen for incoming connections
    server_socket.listen(1)
    print("The server is ready to receive!")

    while True:
        # Accept incoming connection requests
        connection_socket, address = server_socket.accept()

        # Receive a message from the client and decode it
        sentence = connection_socket.recv(1024).decode()

        # Convert the received message to uppercase
        capitalized_sentence = sentence.upper()

        # Send the modified message back to the client
        connection_socket.send(capitalized_sentence.encode())

        # Close the connection with the client
        connection_socket.close()

except Exception as e:
    # Print any errors that occur during execution
    print(f"Error: {e}")