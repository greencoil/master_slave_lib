import time
import serial

if __name__ == '__main__':
    print("Serial Communicater Start")
    ser = serial.Serial('COM5',115200,timeout=None)
    try:
        while True:
            ser.write(0x40)
            print(ser.read())
    except KeyboardInterrupt:
        print('interrupted!') 
        exit()
