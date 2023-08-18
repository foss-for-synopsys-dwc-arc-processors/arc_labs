/* ------------------------------------------
 * Copyright (c) 2018, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */

#include "embARC.h"
#include "embARC_debug.h"

#include "board.h"
#include "device/ip_hal/dev_iic.h"
#include "tcn75.h"

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "httpserver-netconn.h"

#include <stdlib.h>
#include <string.h>

#ifndef HTTPD_DEBUG
#define HTTPD_DEBUG         LWIP_DBG_OFF
#endif

#define TEMP_I2C_ID			DW_IIC_0_ID

char *gcvt(double number, size_t ndigits, char *buf);
static void task_send(void *par);
static void task_temp(void *par);
static void http_server_netconn_serve(struct netconn *conn);

#define TSK_PRIOR_SEND		(configMAX_PRIORITIES-2)
#define TSK_PRIOR_TEMP		(configMAX_PRIORITIES-1)

// Queues
static QueueHandle_t dtq1_id;

// Task IDs
static TaskHandle_t task_send_handle = NULL;
static TaskHandle_t task_temp_handle = NULL;

static char *http_index_number;
static char http_index_html[] = "<html><head><title>Temperature Monitor</title></head><body><h1>Welcome to our Temperature Monitor</h1><p>Now the temperature is ????? *C.</p></body></html>";
static const char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
static const char http_index_html_1[] = "<html><head><title>Temperature Monitor</title></head><body><h1>Welcome to our Temperature Monitor</h1><p>Now the temperature is ";
static const char http_index_html_2[] = " *C.</p></body></html>";


/**
 * \brief  call FreeRTOS API, create and start tasks
 */
int main(void)
{

	vTaskSuspendAll();

	// Create Tasks
	//####Insert code here###

	// Create Queues
	//####Insert code here###

	xTaskResumeAll();

	vTaskSuspend(NULL);

	return 0;
}


static void task_send(void *par)
{
	float temp_val = 0.0;
	struct netconn *conn, *newconn;
	err_t err;

	/* Create a new TCP connection handle */
	/* Bind to port 80 (HTTP) with default IP address */
	conn = netconn_new(NETCONN_TCP);
	netconn_bind(conn, IP_ADDR_ANY, 80);

	/* Put the connection into LISTEN state */
	netconn_listen(conn);

	do
	{
    	err = netconn_accept(conn, &newconn);

    	if (err == ERR_OK)
    	{
    		xQueuePeek(dtq1_id, (void *)(&temp_val), portMAX_DELAY);
    		board_delay_ms(1,1);
        	http_index_number = gcvt((double)(temp_val), 3, http_index_number);

    		http_server_netconn_serve(newconn);
    		netconn_delete(newconn);
		}

	}
	while(err == ERR_OK);

	LWIP_DEBUGF(HTTPD_DEBUG,("http_server_netconn_thread: netconn_accept received error %d, shutting down",err));

	netconn_close(conn);
	netconn_delete(conn);
}


static void task_temp(void *par)
{
	float temp_val = 0.0;

	static portTickType xLastWakeTime;
    const portTickType xFrequency = pdMS_TO_TICKS(1000);

	// 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同
	xLastWakeTime = xTaskGetTickCount();

	//初始化TCN75
	//####Insert code here###

	while (1)
	{
		/* 调用系统延时函数,周期性阻塞1000ms */
        vTaskDelayUntil( &xLastWakeTime,xFrequency );

		//读取TCN75
		//####Insert code here###

		xQueueReset(dtq1_id);
		board_delay_ms(1, 1);
    	xQueueSend(dtq1_id, (void *)(&temp_val),  portMAX_DELAY);
	}
}


/** Serve one HTTP connection accepted in the http thread */
static void http_server_netconn_serve(struct netconn *conn)
{
	struct netbuf *inbuf;
	char *buf;
	u16_t buflen;
	err_t err;

	/* Read the data from the port, blocking if nothing yet there.
	We assume the request (the part we care about) is in one netbuf */
	err = netconn_recv(conn, &inbuf);

	if(err == ERR_OK)
	{
    	netbuf_data(inbuf, (void**)&buf, &buflen);

    	/* Is this an HTTP GET command? (only check the first 5 chars, since
    	there are other formats for GET, and we're keeping it very simple )*/
    	if(buflen>=5 && buf[0]=='G' && buf[1]=='E' && buf[2]=='T' && buf[3]==' ' && buf[4]=='/' )
    	{
    		memset(http_index_html, 0, sizeof(http_index_html)-1);

    		strcat (http_index_html, http_index_html_1);
    		strcat (http_index_html, http_index_number);
    		strcat (http_index_html, http_index_html_2);

    		/* Send the HTML header
             * subtract 1 from the size, since we dont send the \0 in the string
             * NETCONN_NOCOPY: our data is const static, so no need to copy it */
			netconn_write(conn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);

			/* Send our HTML page */
			netconn_write(conn, http_index_html, sizeof(http_index_html)-1, NETCONN_NOCOPY);

		}
  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);
  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}
