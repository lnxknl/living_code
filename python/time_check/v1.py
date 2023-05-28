import time

# Set the timeout
timeout = 4 # seconds

# Set the flag to False by default
flag = False

# Start the timer
start_time = time.time()

# Loop until the flag is set or the timeout is reached
while not flag:
    # Do some work here...

    # Check if the timeout has been reached
    elapsed_time = time.time() - start_time
    if elapsed_time >= timeout:
        break

    # Sleep for a short time to prevent the loop from consuming all resources
    time.sleep(1)

# Check if the flag was set or if the timeout was reached
if flag:
    print("Flag was set!")
else:
    print("Timeout reached!")
