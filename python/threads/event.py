import threading
import time

# Define an Event object to signal when the thread should stop running
stop_event = threading.Event()

# Define a function to run in the thread
def thread_function():
    while not stop_event.is_set():
        # Do some work here...
        print('Thread looping...')
        time.sleep(1)
    print('Thread stopped.')

# Create a thread and start it
thread = threading.Thread(target=thread_function)
thread.start()

# Wait for a while...
time.sleep(5)

# Signal the thread to stop running
stop_event.set()

# Wait for the thread to finish
thread.join()

print('Thread has stopped.')
