#!/usr/bin/python3
"""
ai.py
"""
import sys, os
sys.path.insert(1, os.path.join(sys.path[0], '../communication'))

import time
from serialcom import SerialCom
import def_pb2 as pb
import random

class Ai:
    """
    This is the AI of the robot.
    This code will run on a RaspberryPi, connected through UART (serial) to an IO board.
    It may also use Ivy to communicate with a dedicated HMI to vizualize robot moves.
    """

    PERIOD_CMD = 2

    def __init__(self):
        self.serial = SerialCom("/tmp/virtual-tty")
        self.last_time_cmd = 0

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.serial.close()
        print("exit")

    def main_loop(self):
        """Main loop of the AI"""
        while True:
            msg = self.serial.check_msgs()
            if msg is not None:
                print("received: ", type(msg))
                print(msg)
            
            if time.time() - self.last_time_cmd > Ai.PERIOD_CMD:
                cmd = pb.SpeedCommand()
                cmd.vx = random.randint(-10, 10)
                cmd.vy = 0
                cmd.vtheta = 0.57
                self.serial.send_msg(cmd)
                self.last_time_cmd = time.time()

if __name__ == '__main__':
    with Ai() as ai:
        ai.main_loop()
