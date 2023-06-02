import re
import socket

# Define the host and port to use
HOST = 'localhost'
PORT = 12345
msg = ''


#sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#
## Bind the socket to a specific address and port
#sock.bind((HOST, PORT))
#
## Listen for incoming connections
#sock.listen(1)
#
#while True:
#    # Accept an incoming connection
#    conn, addr = sock.accept()
#    print('Connected by', addr)
#
#    # Receive the message from the first task (task one)
#    data = conn.recv(1024)
#
#    if not data:
#        break
#
#    # Process the message (e.g.,store it in a variable)
#    message = data.decode()
#    print("Task two received:", message)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    print("start")
    s.bind((HOST, PORT))
    s.listen(1)
    conn, addr = s.accept()
    print('Connected by', addr)
    while True:
        try:
            data = conn.recv(1024)
        except OSError as e:
            print(f"Socket error: {e}")
            break

#        while b'\n' not in data:
#            chunk = conn.recv(1024)
#            if not chunk:
#                break
#            data += chunk
        if not data:
            break
#        message = data.decode().strip()
        try:
            message = data.decode('utf-8')
        except UnicodeDecodeError:
            message = data.decode('utf-8', errors='ignore')
#        message = data.decode()
        print('Received:', message)
#        response = f'Echoing back: {message}\n'
#        conn.sendall(response.encode())


#        match = re.match(r'(.+?)：(.+\问题.+) (.+)', message)
#        pattern0 = r'^(.*?)：.*问题\s+(.*)$'
#        pattern1 = r'^(.*?): .*问题\s+(.*)$'
        pattern2 = r'^(.*?): .*@(.+)'
        pattern4 = r'^(.*?)：.*@(.+)'
#        pattern2 = r'(\w+):\s+@(.+)'
#        pattern = r'^(.*?)：.*问题\s+(.*)$'
#        match = re.match(pattern0, message) or re.match(pattern1, message) or re.match(pattern2, message)
        match =  re.match(pattern2, message) or re.match(pattern4,message)


        if match:
            print("match")
            user_name = match.group(1)
            msg = match.group(2)
            tag = True
            print(f'User name: {user_name}')
            print(f'Message: {message}')
            print(f'Tag: {tag}')


        # Modify the message (e.g., convert it to uppercase)
#        modified_message = message.upper()
            modified_message = msg
            send_message = f'{user_name}!!{modified_message}'

    
            # Close the connection
#            conn.close()
    
            # Create a new socket object
            sock_out = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
            # Connect to the third task (task three)
            sock_out.connect((HOST, PORT + 1))
    
            # Send the modified message to the third task
#            sock_out.sendall(modified_message.encode())
            sock_out.sendall(send_message.encode())
    
            # Receive the response from the third task
            response = sock_out.recv(1024)
    
            # Print the response
            print("Task two received response:", response.decode())
    
            # Close the socket
#            sock_out.close()
            print("after close")



        else:
#            conn.close()
            print('No match')
