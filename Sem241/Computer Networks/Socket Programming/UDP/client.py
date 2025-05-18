from socket import *

# Specify server name & port
SERVER_NAME = '192.168.2.46'
SERVER_PORT = 12000

# Create UDP socket
#   AF_INET means that this is gonna be an internet-type IPv4 socket
#   SOCK_DGRAM says that this is 'UDP' datagram socket, rather than 'TCP'
client_socket = socket(AF_INET, SOCK_DGRAM)

# Get user input
message = input('Input a sentence (in lowercase): ')

# Attach server name, port to message, and send into socket
client_socket.sendto(message.encode(), (SERVER_NAME, SERVER_PORT))

# Read reply characters from socket into string
modified_message, server_address = client_socket.recvfrom(2048)

# Print out the received string and close the socket
print(modified_message.decode())
client_socket.close()