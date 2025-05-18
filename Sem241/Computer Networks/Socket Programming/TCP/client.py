from socket import *

# Specify server name & port
SERVER_NAME = '192.168.2.46'
SERVER_PORT = 12000

# Create TCP socket
#   AF_INET means that this is gonna be an internet-type IPv4 socket
#   SOCK_STREAM indicates a TCP socket for streaming data
client_socket = socket(AF_INET, SOCK_STREAM)

# Connect to the server
client_socket.connect((SERVER_NAME, SERVER_PORT))

# Get user input
sentence = input('Input a sentence (in lowercase): ')

# Send the input sentence to the server
client_socket.send(sentence.encode())

# Receive the modified sentence from the server
modified_sentence = client_socket.recv(1024)

# Print the modified sentence received from the server
print('From Server: ', modified_sentence.decode())

# Close the socket connection
client_socket.close()