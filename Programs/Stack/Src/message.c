#include "message.h"
#include <stdlib.h>
#include <string.h>

char* readMessage(char* message) {

    return "0";
}

char* buildMessage(ip_addr_t client_ip, ip_addr_t server_ip, uint16_t client_port, uint16_t server_port, int functionName) {
    char* msg = malloc(MESSAGE_LEN);
    if (!msg) return NULL;

    // 1. Client-IP
    memcpy(&msg[OFFSET_SRC_IP], &client_ip.addr, IP_ADDR_LEN);

    // 2. Server-IP
    memcpy(&msg[OFFSET_DST_IP], &server_ip.addr, IP_ADDR_LEN);

    // 3. Client-Port (Big Endian)
    msg[OFFSET_SRC_PORT]     = (client_port >> 8) & 0xFF;
    msg[OFFSET_SRC_PORT + 1] = client_port & 0xFF;

    // 4. Server-Port (Big Endian)
    msg[OFFSET_DST_PORT]     = (server_port >> 8) & 0xFF;
    msg[OFFSET_DST_PORT + 1] = server_port & 0xFF;

    // 5. Payload / Function Name (Big Endian)
    msg[OFFSET_PAYLOAD]     = (functionName >> 24) & 0xFF;
    msg[OFFSET_PAYLOAD + 1] = (functionName >> 16) & 0xFF;
    msg[OFFSET_PAYLOAD + 2] = (functionName >> 8) & 0xFF;
    msg[OFFSET_PAYLOAD + 3] = functionName & 0xFF;

    return msg;
}


char* readLine() {
    return "0";
}