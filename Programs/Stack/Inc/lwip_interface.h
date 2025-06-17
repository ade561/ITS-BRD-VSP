#ifndef LWIP_INTERFACE_H_
#define LWIP_INTERFACE_H_

#include "lwip/netif.h"

extern struct netif its_brd_netif;

void init_lwip_stack(void);
void netif_config(void);
void check_input(void);

#endif // LWIP_INTERFACE_H_
