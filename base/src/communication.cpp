#include "communication.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include "def.pb.h"
#include <Arduino.h>

enum MessagesId {
    ID_ODOM_REPORT = 0,
    ID_SPEED_CMD = 1,
};


uint16_t compute_cheksum(uint8_t *buffer, size_t len) {
  uint8_t ck_a = 0;
  uint8_t ck_b = 0;
  for(size_t i=0; i<len; i++) {
    ck_a = (ck_a + buffer[i]);       // % 256 by overflow
    ck_b = (ck_b + ck_a);    // % 256 by overflow
  }
  uint16_t ck = ck_a | (ck_b << 8);  // encode as little endian
  return ck;
}

void send_message(uint8_t* buffer, size_t length) {
    buffer[0] = 0xFF;  //schar1
    buffer[1] = 0xFF;  //schar2

    //compute checksum for buffer[3:length-2], or maybe buffer[5:length-2]
    uint16_t chk = compute_cheksum(buffer+2, length-4);
    //compute checksum
    buffer[length-2] = chk >> 8;    //High byte
    buffer[length-1] = chk & 0XFF;  //Low  byte

    Serial.write(buffer, length);
}

int send_odom_report(float pos_x, float pos_y, float pos_theta) {

    uint8_t msg_buf[OdomReport_size + 6];
    // msg_buf[0] and msg_buf[1] reserved for sync chars
    msg_buf[2] = ID_ODOM_REPORT; //ID
    //will fill msg_buf[3] with payload lenght later

    uint8_t* payload_buf = msg_buf + 4; //payload will start from buf[4]

    //create new message, zero initialized
    OdomReport message = OdomReport_init_zero;
    
    ///Fill the message
    message.pos_x = pos_x;
    message.pos_y = pos_y;
    message.pos_theta = pos_theta;

    // Create a stream that will write to our buffer.
    pb_ostream_t stream = pb_ostream_from_buffer(payload_buf, OdomReport_size);
    
    //Now we are ready to encode the message!
    bool status = pb_encode(&stream, OdomReport_fields, &message);
    msg_buf[3] = stream.bytes_written;
    
    /* Then just check for any errors.. */
    if (!status)
    {
        //PB_GET_ERROR(&stream)
        return -1;
    }

    send_message(msg_buf, sizeof(msg_buf));

    return 0;
}

/**
 *  @param speedCmd:    pointer to zero-initialized SpeedCommand that this function will fill in
 *  @param payload_buf: buffer with the payload data (no headers or footers)
 *  @param lenght:      Lenght of payload_buf
 */
  
int deserialize_speed_command(SpeedCommand* speedCmd, uint8_t* payload_buf, int lenght) {
    
    /* Create a stream that reads from the buffer. */
    pb_istream_t stream = pb_istream_from_buffer(payload_buf, lenght);
    
    /* Now we are ready to decode the message. */
    bool status = pb_decode(&stream, SpeedCommand_fields, speedCmd);
    
    /* Check for errors... */
    if (!status)
    {
        //PB_GET_ERROR(&stream);
        return -1;
    }

    return 0;
}