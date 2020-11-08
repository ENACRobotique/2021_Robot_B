#!/usr/bin/python3

from serial import Serial
import time

class Ai:
"""
This is the AI of the robot.
This code will run on a RaspberryPi, connected through UART (serial) to an IO board.
It may also use Ivy to communicate with a dedicated HMI to vizualize robot moves.
"""

    def __init__(self):
        self.serial = Serial("/tmp/virtual-tty")

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.serial.close()
        print("exit")

    def check_messages(self):
        if(self.serial.in_waiting):
            data = self.serial.read(self.serial.in_waiting)
            return data

    def main_loop(self):
        while True:
            msg = self.check_messages()
            if msg is not None:
                print("received: ", msg)
                self.serial.write(b'Chill dude!')

if __name__ == '__main__':
    with Ai() as ai:
        ai.main_loop()
