import os
import signal

# Get the PID of the program you want to interrupt
pid = 3752474

# Send the SIGUSR1 signal to the program with the given PID
os.kill(pid, signal.SIGUSR1)
