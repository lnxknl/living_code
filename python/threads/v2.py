import threading
import time

# Define a global variable to indicate if the thread should be stopped
stop_thread = False

# Define a function to run in the first thread
def thread1_function():
    print('Thread 1 started.')
    while not stop_thread:
        # Do some work here...
        print('Looping...')
        time.sleep(1)
    print('Thread 1 finished.')

# Define a function to run in the second thread
def thread2_function(thread_to_stop):
    print('Thread 2 started.')
    time.sleep(5)
    thread_to_stop()
    print('Thread 2 finished.')

# Create the first thread
thread1 = threading.Thread(target=thread1_function)

# Create the second thread and pass the function to stop the first thread as an argument
thread2 = threading.Thread(target=thread2_function, args=(thread1_function,))

# Start both threads
thread1.start()
thread2.start()

# Wait for both threads to finish
thread1.join()
thread2.join()

print('Both threads finished.')
