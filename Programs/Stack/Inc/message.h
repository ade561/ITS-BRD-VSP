//
// Created by Darius on 08.06.25.
//

#ifndef MESSAGE_H
#define MESSAGE_H


#include <stdint.h>
#include "timer.h"
#include "lwip/ip_addr.h"


#define IP_ADDR_LEN      4
#define PORT_LEN         2
#define PAYLOAD_LEN      4
#define SEQUENCE_LEN     4
#define CHECKSUM_LEN     4
#define MESSAGE_LEN      (2 * IP_ADDR_LEN + 2 * PORT_LEN + PAYLOAD_LEN + SEQUENCE_LEN + CHECKSUM_LEN)

#define OFFSET_SRC_IP    0
#define OFFSET_DST_IP    (OFFSET_SRC_IP + IP_ADDR_LEN)
#define OFFSET_SRC_PORT  (OFFSET_DST_IP + IP_ADDR_LEN)
#define OFFSET_DST_PORT  (OFFSET_SRC_PORT + PORT_LEN)
#define OFFSET_PAYLOAD   (OFFSET_DST_PORT + PORT_LEN)
#define OFFSET_SEQ_NUM   (OFFSET_PAYLOAD + PAYLOAD_LEN)
#define OFFSET_CHECKSUM  (OFFSET_SEQ_NUM + SEQUENCE_LEN)


//Message Payloads

#define NON_SHIFT_NUM_COMMAND_CASES 6
#define SHIFT_NUM_COMMAND_CASES 6


#define MOVE_RIGHT 1
#define MOVE_LEFT 2
#define MOVE_UP 3
#define MOVE_DOWN 4
#define MOVE_FORWARD 5
#define MOVE_BACKWARDS 6
#define OPEN_GRIP 7
#define CLOSE_GRIP 8

#define MOVE_LEFT_TO_RIGHT_UP 9
#define MOVE_RIGHT_TO_LEFT_UP 10
#define MOVE_LEFT_TO_RIGHT_DOWN 11
#define MOVE_RIGHT_TO_LEFT_DOWN 12

#define HEARTBEAT 13
#define ACKNOWLEDGE 14

#define DEFAULT_XCORD 0
#define DEFAULT_YCORD 0

#define HEARTBEAT_INTERVAL (TICKS_PER_US * 5000) // Interval in milliseconds for heartbeat messages

char* readLine();
char* readMessage(char* message);
char* buildMessage(ip_addr_t client_ip, ip_addr_t server_ip, uint16_t client_port, uint16_t server_port, int functionName, uint32_t seqNumber);




#endif //MESSAGE_H
