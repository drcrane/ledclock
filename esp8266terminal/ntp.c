//////////////////////////////////////////////////
// Simple NTP client for ESP8266.
// Copyright 2015 Richard A Burton
// richardaburton@gmail.com
// See license.txt for license terms.
//////////////////////////////////////////////////

//#include <c_types.h>
#include <espressif/user_interface.h>
#include <espressif/esp_wifi.h>
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/dns.h"
#include "FreeRTOS.h"
#include "task.h"
#include <etstimer.h>
#include <espressif/osapi.h>
#include <mem.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ntp.h"
#include "tzstruct.h"

// list of major public servers http://tf.nist.gov/tf-cgi/servers.cgi
//uint8_t ntp_server[] = {131, 107, 13, 100}; // microsoft
uint8_t ntp_server[] = { 129, 250, 35, 250 };
//uint8_t ntp_server[] = {192, 168, 5, 128};

static struct netconn * g_conn;

static ETSTimer ntp_timeout;

static void ntp_udp_timeout(void *arg) {
	
	sdk_os_timer_disarm(&ntp_timeout);
	printf("ERR\r\n");
	//uart0_tx_buffer("ntp timout\r\n", 12);

	// clean up connection
//	if (pCon) {
//		//espconn_delete(pCon);
//		free(pCon->proto.udp);
//		free(pCon);
//		pCon = 0;
//	}
}

static int simpledivide(int input, int divisor) {
	int ctr = 0;
	while (input > divisor) {
		ctr++;
		input -= divisor;
	}
	return ctr;
}

static int simplemod(int input, int divisor) {
	int output;
	output = input - simpledivide(input, divisor) * divisor;
	return output;
}

static void ntp_udp_recv(void *arg, char *pdata, unsigned short len) {
	time_t timestamp;
	time_t temp;
	ntp_t *ntp;
	unsigned int hour;
	unsigned int min;
	unsigned int sec;
	unsigned int addhour;

	//sdk_os_timer_disarm(&ntp_timeout);

	// extract ntp time
	ntp = (ntp_t*)pdata;
	timestamp = (ntp->trans_time[0] & 0xff) << 24 | 
			(ntp->trans_time[1] & 0xff) << 16 |
			(ntp->trans_time[2] & 0xff) << 8 |
			(ntp->trans_time[3] & 0xff);
	// convert to unix time
	timestamp -= 2208988800UL;
	//printf("et %ld\r\n", (long int)timestamp);
	// create tm struct
	//setenv("TZ", "UTC0UTC0,0,0", 1);
	//tzset();
	//dt = gmtime(&timestamp);
	//timestamp = 1537048602L;
	addhour = tz_shouldaddanhour(timestamp);
	timestamp = timestamp - simpledivide(timestamp, 31536000L) * 31536000L;
	//printf("yt %ld\r\n", (long int)timestamp);
	temp = simplemod(timestamp, (24L*60L*60L));
	hour = simplemod(simpledivide(temp, (60L*60L)) + addhour, 24);
	temp = simplemod(temp, (60L*60L));
	min = simpledivide(temp, 60L);
	temp = simplemod(temp, 60L);
	// if you don't do this the returned seconds will be from (and including) 01 to 60
	sec = temp - 1;

	// do something with it, like setting an rtc
	//ds1307_setTime(dt);
	// or just print it out
	//char timestr[11];
	printf("\r\nTIME%02d:%02d:%02d\r\n", hour, min, sec);
	//uart0_tx_buffer(timestr, 10);

	// clean up connection
	//if (pCon) {
	//	espconn_delete(pCon);
	//	free(pCon->proto.udp);
	//	free(pCon);
	//	pCon = 0;
	//}
}

static void netCallback(struct netconn *conn, enum netconn_evt evt, uint16_t length) {
	struct netbuf * netbuf;
	ntp_t * ntp;
	uint16_t ntplen;
	//printf("EVT- %x\r\n", evt);
	sdk_os_timer_disarm(&ntp_timeout);
	if (evt == NETCONN_EVT_RCVPLUS) {
		if (netconn_recv(conn, &netbuf) == ERR_OK) {
			do {
				netbuf_data(netbuf, (void *)&ntp, &ntplen);
				ntp_udp_recv(NULL, (void *)ntp, ntplen);
			} while (netbuf_next(netbuf) >= 0);
			netbuf_delete(netbuf);
			netconn_delete(conn);
		}
	}
}

ip_addr_t g_addr;

void receive_dns_response(const char *name, ip_addr_t *ipaddr, void *callback_arg) {
	//uint8_t * addr;
	//addr = &ipaddr->addr;
	//printf("%d.%d.%d.%d\n", addr[0] & 0xff, addr[1] & 0xff, addr[2] & 0xff, addr[3] & 0xff);
	//ip_addr_t addr;
	// Fire off UDP Request
	struct netbuf *net_buf;
	ntp_t * ntp;
	g_conn = netconn_new_with_callback(NETCONN_UDP, netCallback);
	netconn_connect(g_conn, ipaddr, 123);
	net_buf = netbuf_new();
	ntp = (ntp_t *)netbuf_alloc(net_buf, sizeof(ntp_t));
	memset(ntp, 0, sizeof(ntp_t));
	ntp->options = 0b00100011;
	netconn_send(g_conn, net_buf);
	netbuf_delete(net_buf);
	// now, that would just be silly
	//netconn_delete(g_conn);
	// set timeout timer
	sdk_os_timer_disarm(&ntp_timeout);
	sdk_os_timer_setfn(&ntp_timeout, ntp_udp_timeout, NULL);
	sdk_os_timer_arm(&ntp_timeout, NTP_TIMEOUT_MS, 0);
}

void ntp_get_time(char * hostname) {

	//ntp_t * ntp;
	//ip_addr_t addr;
	//struct netbuf *net_buf;
	//char * data;
	int res;

	// set up the udp "connection"
	/*
	pCon = (struct espconn*)os_zalloc(sizeof(struct espconn));
	pCon->type = ESPCONN_UDP;
	pCon->state = ESPCONN_NONE;
	pCon->proto.udp = (esp_udp*)os_zalloc(sizeof(esp_udp));
	pCon->proto.udp->local_port = espconn_port();
	pCon->proto.udp->remote_port = 123;
	sdk_os_memcpy(pCon->proto.udp->remote_ip, ntp_server, 4);
	*/

	//setenv("TZ", "UTC0UTC0,0,0", 1);
	//tzset();
	LOCK_TCPIP_CORE();
	res = dns_gethostbyname(hostname, &g_addr, (dns_found_callback)receive_dns_response, NULL);
	UNLOCK_TCPIP_CORE();
	if (res == ERR_OK) {
		//printf("Got Addr from NETDB\n");
		receive_dns_response(hostname, &g_addr, NULL);
	}

//	if (1 == 2) {

//	g_conn = netconn_new_with_callback(NETCONN_UDP, netCallback);
	//netconn_set_nonblocking(g_conn, NETCONN_FLAG_NON_BLOCKING);
//	memset(&addr, 0, sizeof(ip_addr_t));
	//addr.type = IPADDR_TYPE_V4;
//	memcpy(&addr.addr, ntp_server, 4);
	//netconn_connect(g_conn, &addr, 8123);
//	netconn_connect(g_conn, &addr, 123);
//	net_buf = netbuf_new();

	//data = netbuf_alloc(net_buf, 10);
	//for (int i = 0x30; i < 0x3a; i++) {
	//	data[i - 0x30] = i;
	//}
	//netconn_send(g_conn, net_buf);
	//

	// create a really simple ntp request packet
	//memset(&ntp, 0, sizeof(ntp_t));
	//ntp.options = 0b00100011; // leap = 0, version = 4, mode = 3 (client)
//	ntp = (ntp_t *)netbuf_alloc(net_buf, sizeof(ntp_t));
//	memset(ntp, 0, sizeof(ntp_t));
//	ntp->options = 0b00100011;
//	netconn_send(g_conn, net_buf);
//	netconn_delete(net_buf);

	// set timeout timer
//	sdk_os_timer_disarm(&ntp_timeout);
//	sdk_os_timer_setfn(&ntp_timeout, ntp_udp_timeout, NULL);
//	sdk_os_timer_arm(&ntp_timeout, NTP_TIMEOUT_MS, 0);

//	}

	// send the ntp request
	//espconn_create(pCon);
	//espconn_regist_recvcb(pCon, ntp_udp_recv);
	//espconn_sent(pCon, (uint8_t*)&ntp, sizeof(ntp_t));
}

