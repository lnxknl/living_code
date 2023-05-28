import threading
import time

# Set the timeout
timeout = 10 # seconds

# Set the flag to False by default
flag = False

# Define the function to run the loop
def loop_function():
    global flag
    while not flag:
        # Do some work here...
        print('Looping...')
        time.sleep(1)

# Define the function to run the timeout check
def timeout_function():
    global flag
    time.sleep(timeout)
    flag = True

# Start the loop in a separate thread
loop_thread = threading.Thread(target=loop_function)
loop_thread.start()

# Start the timeout check in a separate thread
timeout_thread = threading.Thread(target=timeout_function)
timeout_thread.start()

# Wait for the loop thread to finish (which will never happen in this case)
loop_thread.join()

# Check if the flag was set or if the timeout was reached
if flag:
    print("Timeout reached!")
else:
    print("Flag was set!")
