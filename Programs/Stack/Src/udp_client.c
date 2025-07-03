#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "err.h"
#include "ip_addr.h"
#include "lwip/udp.h"
#include "lcd.h"
#include "lwip_interface.h"
#include "LCD_GUI.h"
#include "err.h"
#include "message.h"
#include "output.h"
#include "timer.h"
#include "udp_client.h"
#include "led.h"
#define UDP_SERVER_IP   "192.168.178."  // IP-Adresse des Zielservers
#define UDP_SERVER_PORT 8080            // Port des Zielservers
#define UDP_LOCAL_PORT  5678            // Beliebiger freier lokaler Port

extern volatile uint32_t seqNumber;
static struct udp_pcb *udp_client_pcb = NULL;
static ip_addr_t server_ip;
extern uint64_t currentTime, oldTime;
extern uint8_t heartbeatStatus; 
extern uint8_t keepAliveCounter;

/* Empfangs-Callback */
static void udp_client_recv_callback(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                                     const ip_addr_t *addr, u16_t port) {
    if (p != NULL && p->len >= MESSAGE_LEN) {
        const uint8_t* msg = (const uint8_t*)p->payload;

        ip_addr_t src_ip;
        memcpy(&src_ip.addr, &msg[OFFSET_SRC_IP], IP_ADDR_LEN);

        ip_addr_t dst_ip;
        memcpy(&dst_ip.addr, &msg[OFFSET_DST_IP], IP_ADDR_LEN);

        uint16_t src_port = (msg[OFFSET_SRC_PORT] << 8) | msg[OFFSET_SRC_PORT + 1];
        uint16_t dst_port = (msg[OFFSET_DST_PORT] << 8) | msg[OFFSET_DST_PORT + 1]; 
        // Payload / Function Name  
        int function_name = (msg[OFFSET_PAYLOAD] << 24) | (msg[OFFSET_PAYLOAD + 1] << 16) |
                            (msg[OFFSET_PAYLOAD + 2] << 8) | msg[OFFSET_PAYLOAD + 3];

        uint32_t seq_num = (msg[OFFSET_SEQ_NUM] << 24) | (msg[OFFSET_SEQ_NUM + 1] << 16) |
                           (msg[OFFSET_SEQ_NUM + 2] << 8) | msg[OFFSET_SEQ_NUM + 3];

        uint32_t checksum = (msg[OFFSET_CHECKSUM] << 24) | (msg[OFFSET_CHECKSUM + 1] << 16) |
                            (msg[OFFSET_CHECKSUM + 2] << 8) | msg[OFFSET_CHECKSUM + 3];

        // Checksum-Prüfung
        uint32_t calculated_checksum = 0;
        for (int i = 0; i < MESSAGE_LEN - CHECKSUM_LEN; i++) {
            calculated_checksum += msg[i];
        }
        if (calculated_checksum != checksum) {
            lcdPrintlnS("Checksum Fehler");
            pbuf_free(p);
            return;
        }

        oldTime = TIM2->CNT;
            if((oldTime - currentTime) > HEARTBEAT_INTERVAL && function_name == HEARTBEAT) {
                if(heartbeatStatus == 0) {
                    toggleGPIO(&led_pins[7]);
                }
                keepAliveCounter = 0;
                heartbeatStatus = 1;
                currentTime = oldTime;
                sendMsg(ACKNOWLEDGE);
            }
        
        // Puffer freigeben
        pbuf_free(p);
    } else {
        lcdPrintlnS("Ungueltige Nachricht empfangen");
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

        udp_recv(udp_client_pcb, udp_client_recv_callback, NULL);
		// convert IP address to String
		ipaddr_ntoa_r(&its_brd_netif.ip_addr, ipbuf, sizeof(ipbuf));
		GUI_clear(WHITE);
		// show on display
		lcdPrintS("Local IP:");
		lcdPrintlnS(ipbuf);
        lcdPrintS("zur Verbindung mit einem Server Taste S7 betaetigen");


}


void selectServer(int serverNr) {
    err_t err;
    char ip_str[16];         

    // Nur gültige Oktett-Werte erlauben
    if (serverNr < 1 || serverNr > 253) {
        lcdPrintlnS("Ungueltige Servernummer");
        return;
    }

        //connectionLost();
        disconnectServer();

		// 1. IP-Adresse korrekt zusammensetzen
		snprintf(ip_str, sizeof(ip_str), "%s%d", UDP_SERVER_IP, serverNr);

		// 2. Nun IP-Konvertierung auf ip_str:
		if (!ipaddr_aton(ip_str, &server_ip)) {
			lcdPrintlnS("Ungueltige IP");
			return;
		}

		// 3. Debug-Ausgabe:
		char serverbuf[SERVERBUFFER_SIZE];
		ipaddr_ntoa_r(&server_ip, serverbuf, sizeof(serverbuf));

        err = udp_connect(udp_client_pcb, &server_ip, UDP_SERVER_PORT);
        if (err != ERR_OK) {
            lcdPrintlnS("UDP-Client Connect Fehler");
            udp_remove(udp_client_pcb);
            return;
        }

        GUI_clear(WHITE);
		lcdPrintS("Selected Robot: ");
		lcdPrintlnS(serverbuf);
        lcdPrintlnS("TASTER:");
        lcdPrintlnS("[S0] Rechts  [S1] Links");
        lcdPrintlnS("[S2] Hoch  [S3] Runter");
        lcdPrintlnS("[S4] Vorne  [S5] Hinten");
        lcdPrintlnS("[S6] Shift  [S7] neu verbinden");

        sendMsg(ACKNOWLEDGE);
}


void sendMsg(int number) {
    err_t err;

    char* message = buildMessage(its_brd_netif.ip_addr, server_ip, UDP_LOCAL_PORT, UDP_SERVER_PORT, number, seqNumber++);
    if (!message) return;

    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, MESSAGE_LEN, PBUF_RAM);
    if (p == NULL) {
        lcdPrintlnS("UDP-Client Pufferfehler");
        free(message);
        return;
    }

    memcpy(p->payload, message, MESSAGE_LEN);
    free(message);

    err = udp_sendto(udp_client_pcb, p, &server_ip, UDP_SERVER_PORT);
    if (err != ERR_OK) {
        lcdPrintlnS("UDP-Client Sende Fehler");
        pbuf_free(p);
        return;
    }
    pbuf_free(p);
}


void connectionLost(void) {
    if (udp_client_pcb->remote_port != 0) {
    GUI_clear(WHITE);
    lcdGotoXY(DEFAULT_XCORD, DEFAULT_XCORD);
    udp_disconnect(udp_client_pcb);
    udp_remove(udp_client_pcb);
    udp_client_pcb = NULL;
    setLed(ALL_LEDS, GPIOX_D_LED, LED_OFF);
    lcdPrintlnS("Verbindung getrennt zum Roboter.");
    lcdPrintlnS("Falls erneut verbunden werden soll, bitte ITS-BRD reset Taster betaetigen.");
    toggleGPIO(&led_pins[7]);
    keepAliveCounter = 0;
    }
}

void disconnectServer(void) {
    if (udp_client_pcb != NULL) {
        oldTime = 0;
        currentTime = 0;
        heartbeatStatus = 0;
        keepAliveCounter = 0;
        sendMsg(DISCONNECT);
        udp_disconnect(udp_client_pcb);
        setLed(ALL_LEDS, GPIOX_D_LED, LED_OFF);
        setLed(ALL_LEDS, GPIOX_E_LED, LED_OFF);
    }
}

