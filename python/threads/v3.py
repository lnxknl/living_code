import threading
import time

# Define a global variable to indicate if the threads should be stopped
stop_threads = False

stop_event = threading.Event()
# Define a function to run in the first thread
def thread1_function():
    while stop_event.is_set():
        # Do some work here...
        print('Thread 1 looping...')
        time.sleep(1)
    print('Thread 1 stopped.')

# Define a function to run in the second thread
def thread2_function():
    time.sleep(3)
    stop_event.set()
    print('Thread 2 stopped.')

# Create the first thread
thread1 = threading.Thread(target=thread1_function)

# Create the second thread
thread2 = threading.Thread(target=thread2_function)

# Start both threads
thread1.start()
thread2.start()

# Wait for a while...
time.sleep(5)

# Signal the threads to stop running
stop_threads = True

# Wait for both threads to finish
thread1.join()
thread2.join()

print('Both threads stopped.')
