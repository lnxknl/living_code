import sys
import socket

# Server configuration
HOST = 'localhost'
PORT = 32349

# Check if the message argument is provided
if len(sys.argv) < 2:
    print("Usage: python client.py [message]")
    sys.exit(1)

# Extract the message from command-line arguments
message = ' '.join(sys.argv[1:])

# Create a socket object
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
client_socket.connect((HOST, PORT))
print("Connected to server:", HOST, PORT)

# Send the message to the server
client_socket.sendall(message.encode('utf-8'))

# Receive the response from the server
response = client_socket.recv(1024).decode('utf-8')
print("Server response:", response)

# Close the client socket
client_socket.close()

