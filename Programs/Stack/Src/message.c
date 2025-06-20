#include "message.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include "lcd.h"


volatile uint32_t seqNumber = 0;

char* readMessage(char* message) {

    return "0";
}

char* buildMessage(ip_addr_t client_ip, ip_addr_t server_ip, uint16_t client_port, uint16_t server_port, int functionName, uint32_t seqNumber) {
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

    // 6. Sequence Number (Big Endian)
    msg[OFFSET_SEQ_NUM]     = (seqNumber >> 24) & 0xFF;
    msg[OFFSET_SEQ_NUM + 1] = (seqNumber >> 16) & 0xFF;
    msg[OFFSET_SEQ_NUM + 2] = (seqNumber >> 8) & 0xFF;
    msg[OFFSET_SEQ_NUM + 3] = seqNumber & 0xFF;

    // 7. Checksum (Big Endian)
    uint32_t checksum = 0;
    for (int i = 0; i < MESSAGE_LEN - CHECKSUM_LEN; i++) {
        checksum += (uint8_t)msg[i];
    }
    msg[OFFSET_CHECKSUM]     = (checksum >> 24) & 0xFF;
    msg[OFFSET_CHECKSUM + 1] = (checksum >> 16) & 0xFF;
    msg[OFFSET_CHECKSUM + 2] = (checksum >> 8) & 0xFF;
    msg[OFFSET_CHECKSUM + 3] = checksum & 0xFF;

    // Debugging output
    //lcdPrintS("Checksum: ");
    //lcdPrintInt(checksum);
    return msg;
}


char* readLine() {
    return "0";
}