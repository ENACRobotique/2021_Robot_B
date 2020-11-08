#/bin/sh
socat PTY,link=/tmp/robot-sim,raw,echo=0 PTY,link=/tmp/virtual-tty,raw,echo=0

