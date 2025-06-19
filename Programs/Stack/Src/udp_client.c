#include <stdlib.h>
#include <string.h>
#include "err.h"
#include "lwip/udp.h"
#include "lcd.h"
#include "lwip_interface.h"
#include "LCD_GUI.h"
#include "err.h"
#include "message.h"

#define UDP_SERVER_IP   "192.168.178."  // IP-Adresse des Zielservers
#define UDP_SERVER_PORT 8080            // Port des Zielservers
#define UDP_LOCAL_PORT  5678            // Beliebiger freier lokaler Port

static struct udp_pcb *udp_client_pcb = NULL;
static ip_addr_t server_ip;

/* Nachricht an den Server */
static const char udp_msg[] = "SIKIM";

/* Empfangs-Callback */
static void udp_client_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                                     const ip_addr_t *addr, u16_t port) {
    if (p != NULL) {
        char buffer[128];
        memcpy(buffer, p->payload, p->len > 127 ? 127 : p->len);
        buffer[p->len > 127 ? 127 : p->len] = '\0';

        lcdPrintS("UDP Antwort: ");
        lcdPrintlnS(buffer);

        pbuf_free(p);
    }
}

void udp_client_init(void) {
		char ipbuf[16];  // Maximal formatierte IPv4-Adresse ist "255.255.255.255\0" = 16 Zeichen
    err_t err;

    // Neues UDP PCB erzeugen
    udp_client_pcb = udp_new();
    if (udp_client_pcb == NULL) {
        lcdPrintlnS("UDP-Client PCB Fehler");
        return;
    }

    // Lokalen Port binden
	err = udp_bind(udp_client_pcb, &its_brd_netif.ip_addr, UDP_LOCAL_PORT);
    if (err != ERR_OK) {
        lcdPrintlnS("UDP-Client Bind Fehler");
        udp_remove(udp_client_pcb);
        return;
    }


		// convert IP address to String
		ipaddr_ntoa_r(&its_brd_netif.ip_addr, ipbuf, sizeof(ipbuf));
		GUI_clear(WHITE);
		// show on display
		lcdPrintS("Local IP:");
		lcdPrintlnS(ipbuf);

}


void selectServer(int serverNr) {
    err_t err;
    char ip_str[16];         

    // Nur gültige Oktett-Werte erlauben
    if (serverNr < 1 || serverNr > 253) {
        lcdPrintlnS("Ungueltige Servernummer");
        return;
    }

		// 1. IP-Adresse korrekt zusammensetzen
		snprintf(ip_str, sizeof(ip_str), "%s%d", UDP_SERVER_IP, serverNr);
		lcdPrintlnS(ip_str);

		// 2. Nun IP-Konvertierung auf ip_str:
		if (!ipaddr_aton(ip_str, &server_ip)) {
			lcdPrintlnS("Ungueltige IP");
			return;
		}

		// 3. Debug-Ausgabe:
		char serverbuf[16];
		ipaddr_ntoa_r(&server_ip, serverbuf, sizeof(serverbuf));
		lcdPrintS("Selected Robot: ");
		lcdPrintlnS(serverbuf);
}


void sendMsg(int number) {
    err_t err;

    char* message = buildMessage(its_brd_netif.ip_addr, server_ip, UDP_LOCAL_PORT, UDP_SERVER_PORT, number);
    if (!message) return;

    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, MESSAGE_LEN, PBUF_RAM);
    if (p == NULL) {
        lcdPrintlnS("UDP-Client Pufferfehler");
        free(message);
        return;
    }

    memcpy(p->payload, message, MESSAGE_LEN);
    free(message);

    err = udp_sendto_if(udp_client_pcb, p, &server_ip, UDP_SERVER_PORT, &its_brd_netif);
    pbuf_free(p);
}
