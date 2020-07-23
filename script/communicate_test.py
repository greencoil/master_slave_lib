import time
import serial
import struct

def send( buf ):
      while True:
            if ser.out_waiting == 0:
                  break
      for b in buf:
            a = struct.pack( "B", b )
            ser.write(a)
      ser.flush()

if __name__ == '__main__':
    print("Serial Communicater Start")
    ser = serial.Serial('/dev/ttyACM0',115200,timeout=None)
    try:
        i = 0
        while True:
            # x = [0xFF]
            if i >= 255:
                i = 0
            x =  struct.pack( "B", i )
            send(x)
            time.sleep(0.01)
            res=[]
            while(ser.in_waiting > 0):
                recv_data = ser.read()
                # print(type(recv_data))
                a = struct.unpack_from("B",recv_data ,0)
                res.append(a)
            print(res)
            i+=1
    except KeyboardInterrupt:
        print('interrupted!') 
        exit()
