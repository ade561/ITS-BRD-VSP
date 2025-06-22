#ifndef __UDP_CLIENT_H
#define __UDP_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lwip/udp.h"
#include "lwip/ip_addr.h"

#define SERVERBUFFER_SIZE 16
/**
 * @brief  Initialisiert den UDP-Client und sendet eine Nachricht
 */
void udp_client_init(void);
void selectServer(int serverNr);
void sendMsg(int number);

#ifdef __cplusplus
}
#endif

#endif /* __UDP_CLIENT_H */
