#!/usr/bin/python3
"""
simulator.py
"""
import sys, os
sys.path.insert(1, os.path.join(sys.path[0], '../communication'))

import time
from serialcom import SerialCom
import def_pb2 as pb

class Simulator:
    """
    This is a simulator for the robot IO board.
    This code will not be used in the final robot, it will be used for development only.
    It should receive speed commands (from the AI) and compute the robot's position accordingly.
    It will also send back its position periodicaly (10Hz is a good stating point).

    Ideally, it should model a "realistic" robot: speed should change like a first order.

    Errors may also be introduced to test the robustness of the AI.

    """

    PERIOD_ODOM_REPORT = 1

    def __init__(self):
        self.serial = SerialCom("/tmp/robot-sim")
        self.last_time_odom_report = 0
        self.update_period = 1  # it shall obviously be much lower
        self.sp_vx = 0      # speed setpoint (mm/s)
        self.sp_vtheta = 0  # rotation speed setpoint (rad/s)
        self.vx = 0         # speed
        self.vtheta = 0     # rotation speed
        self.pos_x = 0
        self.pos_y = 0
        self.pos_theta = 0

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.serial.close()
        print("exit")
    
    def update_position(self):
        # TODO
        self.pos_x = self.pos_x + self.vx*self.update_period

    def run(self):
        """Runs commands received via serial and"""
        while True:
            msg = self.serial.check_msgs()
            if msg is not None:
                print("received: ", type(msg))
                print(msg)
                if(type(msg) == pb.SpeedCommand):
                    self.vx = msg.vx
            
            print("compute new state!")
            self.update_position()
            
            if time.time() - self.last_time_odom_report > Simulator.PERIOD_ODOM_REPORT:
                report = pb.OdomReport()
                report.pos_x = self.pos_x
                report.pos_y = self.pos_y
                report.pos_theta = self.pos_theta
                self.serial.send_msg(report)
                self.last_time_odom_report = time.time()
            time.sleep(self.update_period)

if __name__ == '__main__':
    with Simulator() as sim:
        while True:
            sim.run()
