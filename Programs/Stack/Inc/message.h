//
// Created by Darius on 08.06.25.
//

#ifndef MESSAGE_H
#define MESSAGE_H


#include <stdint.h>
#include "lwip/ip_addr.h"


#define IP_ADDR_LEN      4
#define PORT_LEN         2
#define PAYLOAD_LEN      4
#define MESSAGE_LEN      (2 * IP_ADDR_LEN + 2 * PORT_LEN + PAYLOAD_LEN)

#define OFFSET_SRC_IP    0
#define OFFSET_DST_IP    (OFFSET_SRC_IP + IP_ADDR_LEN)
#define OFFSET_SRC_PORT  (OFFSET_DST_IP + IP_ADDR_LEN)
#define OFFSET_DST_PORT  (OFFSET_SRC_PORT + PORT_LEN)
#define OFFSET_PAYLOAD   (OFFSET_DST_PORT + PORT_LEN)




char* readLine();
char* readMessage(char* message);
char* buildMessage(ip_addr_t client_ip, ip_addr_t server_ip, uint16_t client_port, uint16_t server_port, int functionName);




#endif //MESSAGE_H
