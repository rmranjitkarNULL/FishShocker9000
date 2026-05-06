import time
import keyboard
from pySerialTransfer import pySerialTransfer as txfer

SERIAL_PORT = "/dev/ttyACM0"

if __name__ == '__main__':
    try:
        link = txfer.SerialTransfer(SERIAL_PORT)
        link.open()
        time.sleep(3)

        print("Ready to send character inputs...")

        while True:
            key = keyboard.read_key()   # returns a string (character)

            if len(key) != 1:
                continue

            send_size = 0
            send_size += link.tx_obj(key)   # send char
            link.send(send_size)

            print(f"SENT: '{key}'")

            while not link.available():
                pass

            recv_key = link.rx_obj(obj_type=str, obj_byte_size=1)
            print(f"RCVD: '{recv_key}'\n")

    except KeyboardInterrupt:
        print("\nExiting...")
        link.close()
