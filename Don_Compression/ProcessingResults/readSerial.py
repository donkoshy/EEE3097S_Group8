from glob import escape
import serial
import csv

serialPort = serial.Serial(port = "/dev/tty.usbserial-0001", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
serialString = ""                           # Used to hold data coming over UART
#fieldsH = ['Data']

with open ('imuData.txt', 'w', newline="") as f:
    writer = csv.writer(f)
    #writer.writerow(fieldsH)

while(1):
    # Wait until there is data waiting in the serial buffer
    if(serialPort.in_waiting > 0):
        serialString = serialPort.readline()
        if  (len(serialString.decode("latin-1"))>5):
            rows = serialString.decode('latin-1').split(",")
            with open ('imuData.txt' , 'a' ,newline="") as f:
                # Read data out of the buffer until a carraige return / new line is found
                writer = csv.writer(f,delimiter=',', escapechar="%")
                writer.writerow(rows)
                # Print the contents of the serial data
            print(serialString.decode('latin-1')) 
            
