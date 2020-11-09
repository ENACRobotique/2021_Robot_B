
# Simulator

This directory contains the simulator that will be used for the devlopment of the robot. The simulator aims at replacing the IO board and lower layers.

## Virtual serial ports

The IO board will be in fine connected to the raspberryPi via serial.

`emulate_serial_ports.sh` create two virtual serial ports connected to ech others: `/tmp/robot-sim` and `/tmp/virtual-tty`. Data written to /tmp/robot-sim will be read from /tmp/virtual-tty and vice-versa.

The simulator must then use `/tmp/robot-sim`, and the AI must use `/tmp/virtual-tty`.

To run the AI with the real IO board, simply change `/tmp/virtual-tty` to the actual serial port of the IO board.

