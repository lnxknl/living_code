import threading
import time

# Define a function to run in the first thread
def thread1_function():
    print('Thread 1 started.')
    time.sleep(10)
    print('Thread 1 finished.')

# Define a function to run in the second thread
def thread2_function(thread_to_kill):
    print('Thread 2 started.')
    time.sleep(5)
    thread_to_kill.kill()
    print('Thread 2 finished.')

# Create the first thread
thread1 = threading.Thread(target=thread1_function)

# Create the second thread and pass the first thread as an argument
thread2 = threading.Thread(target=thread2_function, args=(thread1,))

# Start both threads
thread1.start()
thread2.start()

# Wait for both threads to finish
thread1.join()
thread2.join()

print('Both threads finished.')
