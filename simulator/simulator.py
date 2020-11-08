#!/usr/bin/python3

from serial import Serial
import time

class Simulator:
"""
This is a simulator for the robot IO board.
This code will not be used in the final robot, it will be used for development only.
It should receive speed commands (from the AI) and compute the position of the robot accordingly.
It will also send back its position periodicaly (10Hz is a good stating point).

Ideally, it should model a "realistic" robot: speed should change like a first order.

Errors may also be introduced to test the robustness of the AI.

"""

    def __init__(self):
        self.serial = Serial("/tmp/robot-sim")
        self.update_period = 1  # it shall obviously be much lower
        self.sp_vx = 0      # speed setpoint (mm/s)
        self.sp_vtheta = 0  # rotation speed setpoint (rad/s)
        self.vx = 0         # speed
        self.vtheta = 0     # rotation speed

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.serial.close()
        print("exit")

    def check_messages(self):
        if(self.serial.in_waiting):
            data = self.serial.read(self.serial.in_waiting)
            return data

    def run(self):
        while True:
            msg = self.check_messages()
            if msg is not None:
                print("received: ", msg)
            print("compute new state!")
            self.serial.write(b"I pretend to be IO board. Where do I go?\r\n")
            time.sleep(self.update_period)

if __name__ == '__main__':
    with Simulator() as sim:
        while True:
            sim.run()

