import time
import keyboard
import re
import serial

from pySerialTransfer import pySerialTransfer as txfer


SERIAL_PORT = 'COM3'

if __name__ == '__main__':
    try:
        link = txfer.SerialTransfer(SERIAL_PORT)
        
        link.open()
        
        time.sleep(2)
        print("Ready to send inputs...")
        
        while True:
                
            if re.fullmatch("^[0-9]+$", keyboard.read_key()):
                send_size = 0
            	
                list_ = int(keyboard.read_key())
                list_size = link.tx_obj(list_)
                send_size += list_size

                link.send(send_size)
            
                while not link.available():
                    pass

                rec_list_  = link.rx_obj(obj_type=type(list_),
                                         obj_byte_size=list_size,
                                         list_format='i')

                print(f'SENT: {list_}')
                print(f'RCVD: {rec_list_}')
                print(' ')
    
    except KeyboardInterrupt:
        link.close()

