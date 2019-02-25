import serial
import time
import RPi.GPIO as GPIO # Import Raspberry Pi GPIO library

import logging
import sys
import time

from Adafruit_BNO055 import BNO055

isConnected = False

bno = BNO055.BNO055(serial_port='/dev/serial0', rst=18)

# Enable verbose debug logging if -v is passed as a parameter.
if len(sys.argv) == 2 and sys.argv[1].lower() == '-v':
    logging.basicConfig(level=logging.DEBUG)
    
    
while isConnected == False:
    try:
        # Initialize the BNO055 and stop if something went wrong.
        bno.begin()
    except (serial.SerialException, RuntimeError):
        print("Trying to connect with the BNO055...\n")
    else:
        print("Connected to port /dev/serial0")
        isConnected == True
        # Print system status and self test result.
        status, self_test, error = bno.get_system_status()
        print('System status: {0}'.format(status))
        print('Self test result (0x0F is normal): 0x{0:02X}'.format(self_test))
        # Print out an error if system status is in error mode.
        if status == 0x01:
            print('System error: {0}'.format(error))
            print('See datasheet section 4.3.59 for the meaning.')

        # Print BNO055 software revision and other diagnostic data.
        sw, bl, accel, mag, gyro = bno.get_revision()
        print('Software version:   {0}'.format(sw))
        print('Bootloader version: {0}'.format(bl))
        print('Accelerometer ID:   0x{0:02X}'.format(accel))
        print('Magnetometer ID:    0x{0:02X}'.format(mag))
        print('Gyroscope ID:       0x{0:02X}\n'.format(gyro))

        print('Reading BNO055 data, press Ctrl-C to quit...')
        break

#GPIO.setwarnings(False) # Ignore warning for now
#GPIO.setmode(GPIO.BOARD) # Use physical pin numbering
#GPIO.setup(4, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) # Set pin 10 to be an input pin and set initial value to be pulled low (off)
GPIO.setup(18, GPIO.OUT)#, pull_up_down=GPIO.PUD_DOWN) 

isConnected = False

while isConnected == False:

    try:
        port =serial.Serial(
            '/dev/ttyACM1',
            baudrate=115200,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            writeTimeout = 0,
            timeout = 1)
    except (serial.SerialException, RuntimeError):
        print("Trying to connect with the v5...\n")
    else:
        print("Connected to port /dev/ttyACM1")
        isConnected == True
        break


buttonPush = 0

print(port.isOpen()) 
print("Port opened... Sending data to v5 now.") 
port.flush()
i=0
while True:
    #print(port.isOpen())
    
        
    
    #print(port.readline())
    i+=1
    #time.sleep(0.1)
    #data=bytes(str(buttonPush).encode())
    #print(data)
    ##response=port.read(1)
    ##print(response)
    #print ("Data Received")
    #port.write(data)
    #port.write(bytes("\n".encode()))
    #print("Data sent")
    #port.write(bytes("\n".encode()))
    
    port.write(str(0b10000000).encode())
    port.write(str(0b01111111).encode())

    
    # Read the Euler angles for heading, roll, pitch (all in degrees).
    heading, roll, pitch = bno.read_euler()
    # Read the calibration status, 0=uncalibrated and 3=fully calibrated.
    sys, gyro, accel, mag = bno.get_calibration_status()
    # Print everything out.
    #buttonPush = GPIO.input(4)
    #print(buttonPush)
    #if buttonPush:
        #headoffset = -1 * heading
        #GPIO.output(18,1)
        #time.sleep(0.1)
        #GPIO.output(18,0)
        
                
    #heading = heading + headoffset
    print('Heading={0:07.3F} Roll={1:0.2F} Pitch={2:0.2F}\tSys_cal={3} Gyro_cal={4} Accel_cal={5} Mag_cal={6}'.format(
          int(heading), roll, pitch, sys, gyro, accel, mag))
    head = bytes("{0:07.3F}".format(heading).encode())
    port.write(head)
    #port.write(bytes("\n".encode()))
    # Other values you can optionally read:
    # Orientation as a quaternion:
    #x,y,z,w = bno.read_quaterion()
    # Sensor temperature in degrees Celsius:
    #temp_c = bno.read_temp()
    # Magnetometer data (in micro-Teslas):
    #x,y,z = bno.read_magnetometer()
    # Gyroscope data (in degrees per second):
    #x,y,z = bno.read_gyroscope()
    # Linear acceleration data (i.e. acceleration from movement, not gravity--
    # returned in meters per second squared):
    x,y,z = bno.read_linear_acceleration()
    # Accelerometer data (in meters per second squared):
    #x,y,z = bno.read_accelerometer()
    port.write(bytes("{0:07.3F}".format(x).encode()))
    port.write(bytes("{0:07.3F}".format(y).encode()))
    port.write(bytes("{0:07.3F}".format(z).encode()))
    #port.write(bytes("\n".encode()))

    # Gravity acceleration data (i.e. acceleration just from gravity--returned
    # in meters per second squared):
    #x,y,z = bno.read_gravity()
    #print(x)
    #print(y)
    #print(z)
    
    time.sleep(0.002)
    port.flush()
    port.reset_input_buffer()
    port.reset_output_buffer()
    #print(i)
    #if i > 100:
    
