import serial
import time
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library

#GPIO.setwarnings(False) # Ignore warning for now
GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
GPIO.setup(10, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)


port =serial.Serial(
    '/dev/ttyACM1',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    writeTimeout = 0,
    timeout = 1)
buttonPush = 0

print(port.isOpen()) 
print("Port opened...") 
port.flush()
i=0
while True:
    buttonPush = GPIO.input(10)
    #print(port.readline())
    i+=1
    #time.sleep(0.1)
    data=bytes(str(buttonPush).encode())
    print(data)
    ##response=port.read(1)
    ##print(response)
    #print ("Data Received")
    port.write(data)
    port.write(bytes("\n".encode()))
    print("Data sent")
    port.reset_input_buffer()
    port.reset_output_buffer()
    time.sleep(0.05)
    port.flush()
