#!/usr/bin/python3
import serial
import time
import bitstring
import sys
import time
from enum import Enum
import def_pb2 as pb


MESSAGES = {
    0: pb.OdomReport,
    1: pb.SpeedCommand
}

class SerialCom:

    class RcvState(Enum):
        Idle = 0
        Start1st = 1
        Start2nd = 2
        MsgId = 3
        MsgLen = 4
        Chk = 5
        

    def __init__(self, port, baudrate=115200):
        self.serial = serial.Serial(port, baudrate, timeout=0.01)
        self._rcv_state = SerialCom.RcvState.Idle
        self._nb_bytes_expected = 1
        self._msg_id = 0
        self._msg_len = 0
        self._payload = b''

    def check_msgs(self):
        """
        Non-blocking method getting messages
        """
        while self.serial.in_waiting >= self._nb_bytes_expected:
            if self._rcv_state == SerialCom.RcvState.Idle:
                # wait for 0XFF
                if ord(self.serial.read()) == 0xFF:
                    self._rcv_state = SerialCom.RcvState.Start1st
                else:
                    # fallback to Idle
                    self._rcv_state = SerialCom.RcvState.Idle

            elif self._rcv_state == SerialCom.RcvState.Start1st:
                if ord(self.serial.read()) == 0xFF:
                    self._rcv_state = SerialCom.RcvState.Start2nd
                else:
                    # fallback to Idle
                    self._rcv_state = SerialCom.RcvState.Idle

            elif self._rcv_state == SerialCom.RcvState.Start2nd:
                # read message ID
                self._msg_id = ord(self.serial.read())
                self._rcv_state = SerialCom.RcvState.MsgId

            elif self._rcv_state == SerialCom.RcvState.MsgId:
                # read payload lenght
                self._msg_len = ord(self.serial.read())
                self._nb_bytes_expected = self._msg_len
                self._rcv_state = SerialCom.RcvState.MsgLen

            elif self._rcv_state == SerialCom.RcvState.MsgLen:
                # read payload
                self._payload = self.serial.read(self._msg_len)       # read message content
                self._nb_bytes_expected = 2
                self._rcv_state = SerialCom.RcvState.Chk

            elif self._rcv_state == SerialCom.RcvState.Chk:
                # read checksum
                chk = self.serial.read(2)
                # Go back to Idle state
                self._rcv_state = SerialCom.RcvState.Idle
                self._nb_bytes_expected = 1
                buffer_to_check = chr(self._msg_id).encode() + chr(self._msg_len).encode() + self._payload
                if self.control_checksum(buffer_to_check, chk):
                    msg = MESSAGES[self._msg_id]()
                    msg.ParseFromString(self._payload)
                    return msg                 # We are now synchronised !
                else:
                    print("chk fail") 
                    return None

    def next_message(self):
        """
        Blocking function until a message is received
        """
        while(True):
            msg = self.check_msgs()
            if msg is not None:
                return msg
            time.sleep(0.001)
    
    def flush_input(self):
        """
        Discard all input bytes.
        """
        while self.serial.in_waiting > 0:
            self.serial.read(self.serial.in_waiting)

    @staticmethod
    def calculate_checksum(msg_bytes):
        """
        Compute checksum for an array of bytes
        """
        ck_a = 0
        ck_b = 0
        for c in msg_bytes:
            ck_a = (ck_a + c) % 256
            ck_b = (ck_b + ck_a) % 256
        ck = (ck_a<<8) | ck_b
        return ck
    
    @staticmethod
    def control_checksum(to_check, chk):
        """
        Compare received checksum with locally computed checksum
        Return: True if checksums matches else False
        """
        ck = SerialCom.calculate_checksum(to_check)
        s = bitstring.BitStream(chk)
        rcv_ck, = s.unpack('uintle:16')         # coma to unpack the list as tuple
        if ck == rcv_ck:
            return True
        else:
            return False


    def send_msg(self, msg):
        start = bitstring.pack('uintle:16', 0XFFFF)
        payload = msg.SerializeToString()
        msg_id = 0
        # get message ID.
        for id, cls in MESSAGES.items():
            if(type(msg) == cls):
                msg_id = id
                break
        else:
            print("msg type not registered!")

        msg_len = len(payload)
        to_check = chr(msg_id).encode() + chr(msg_len).encode() + payload
        chk = self.calculate_checksum(to_check)
        msg_stream = start + chr(msg_id).encode() + chr(msg_len).encode() + payload + bitstring.pack('uintle:16', chk)
        msg_bytes = msg_stream.tobytes()
        self.serial.write(msg_bytes)
    
    def close(self):
        self.serial.close()
        

if __name__ == '__main__':
    sercom = SerialCom(sys.argv[1], int(sys.argv[2]))
    while(True):
        msg = sercom.next_message()
        print(msg)

