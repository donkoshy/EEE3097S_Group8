# Importing the library
import psutil
 
# Calling psutil.cpu_precent() for 4 seconds
print('The CPU usage is: ', psutil.cpu_percent(4))

# Getting % usage of virtual_memory ( 3rd field)
print('RAM memory % used:', psutil.virtual_memory()[2])