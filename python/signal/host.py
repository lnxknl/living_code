import os
import signal
import time

# Define the signal handler function
def signal_handler(signum, frame):
    print('Signal handler called with signal', signum)
    global interrupted
    interrupted = True

# Set the signal handler for SIGUSR1
signal.signal(signal.SIGUSR1, signal_handler)

# Loop until interrupted
interrupted = False
while not interrupted:
    # Do some work here...
    print('Looping...')

    # Sleep for a short time to prevent the loop from consuming all resources
    time.sleep(1)

print('Loop interrupted!')
