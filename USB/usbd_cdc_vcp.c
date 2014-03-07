/**
 ******************************************************************************
 * @file    usbd_cdc_vcp.c
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    22-July-2011
 * @brief   Generic media access Layer.
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED 
#pragma     data_alignment = 4 
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_vcp.h"
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_conf.h"

#include "Util.h"
#include <string.h>

extern uint8_t APP_Rx_Buffer   [APP_RX_DATA_SIZE]; 
extern uint8_t APP_Tx_Buffer   [APP_TX_DATA_SIZE];

/* Ok this is ugly, but works for now */
extern uint32_t APP_Rx_length;
extern bool usbd_cdc_TxBusy();
extern void usbd_cdc_TxStart( int len );


typedef struct
{
  uint32_t bitrate;
  uint8_t  format;
  uint8_t  paritytype;
  uint8_t  datatype;
}LINE_CODING;

#define DEFAULT_CONFIG                  0
#define OTHER_CONFIG                    1

/* Private variables ---------------------------------------------------------*/
LINE_CODING linecoding = {
		115200, /* baud rate*/
		0x00, /* stop bits-1*/
		0x00, /* parity - none*/
		0x08 /* nb. of bits 8*/
};

/* Private function prototypes -----------------------------------------------*/
static uint16_t VCP_Init(void);
static uint16_t VCP_DeInit(void);
static uint16_t VCP_Ctrl(uint32_t Cmd, uint8_t* Buf, uint32_t Len);
static uint16_t VCP_DataRx(uint8_t* Buf, uint32_t Len);

__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

CDC_IF_Prop_TypeDef VCP_fops = { VCP_Init, VCP_DeInit, VCP_Ctrl, VCP_DataTx,
		VCP_DataRx };

void VCP_ModuleInit(void)
{
	USBD_Init( &USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb );
}

/* Private functions ---------------------------------------------------------*/
/**
 * @brief  VCP_Init
 *         Initializes the Media on the STM32
 * @param  None
 * @retval Result of the opeartion (USBD_OK in all cases)
 */
static uint16_t VCP_Init(void) {
	return USBD_OK;
}

/**
 * @brief  VCP_DeInit
 *         DeInitializes the Media on the STM32
 * @param  None
 * @retval Result of the opeartion (USBD_OK in all cases)
 */
static uint16_t VCP_DeInit(void) {
	return USBD_OK;
}

/**
 * @brief  VCP_Ctrl
 *         Manage the CDC class requests
 * @param  Cmd: Command code
 * @param  Buf: Buffer containing command data (request parameters)
 * @param  Len: Number of data to be sent (in bytes)
 * @retval Result of the opeartion (USBD_OK in all cases)
 */
static uint16_t VCP_Ctrl(uint32_t Cmd, uint8_t* Buf, uint32_t Len) {
	switch (Cmd) {
	case SEND_ENCAPSULATED_COMMAND:
		/* Not  needed for this driver */
		break;

	case GET_ENCAPSULATED_RESPONSE:
		/* Not  needed for this driver */
		break;

	case SET_COMM_FEATURE:
		/* Not  needed for this driver */
		break;

	case GET_COMM_FEATURE:
		/* Not  needed for this driver */
		break;

	case CLEAR_COMM_FEATURE:
		/* Not  needed for this driver */
		break;

	case SET_LINE_CODING:
		/* Not  needed for this driver */
		break;

	case GET_LINE_CODING:
		Buf[0] = (uint8_t) (linecoding.bitrate);
		Buf[1] = (uint8_t) (linecoding.bitrate >> 8);
		Buf[2] = (uint8_t) (linecoding.bitrate >> 16);
		Buf[3] = (uint8_t) (linecoding.bitrate >> 24);
		Buf[4] = linecoding.format;
		Buf[5] = linecoding.paritytype;
		Buf[6] = linecoding.datatype;
		break;

	case SET_CONTROL_LINE_STATE:
		/* Not  needed for this driver */
		break;

	case SEND_BREAK:
		/* Not  needed for this driver */
		break;

	default:
		break;
	}

	return USBD_OK;
}

uint8_t* VCP_TxBuffer()
{
	return APP_Tx_Buffer;
}

uint16_t VCP_StartTx( uint32_t Len )
{
	if( usbd_cdc_TxBusy() )
		return -1;

	int len = min( Len,  APP_TX_DATA_SIZE );

	usbd_cdc_TxStart( len );
		return -1;

	return len;
}

uint16_t VCP_DataTx( uint8_t* Buf, uint32_t Len)
{
	if( usbd_cdc_TxBusy() )
		return -1;

	int len = min( Len,  APP_TX_DATA_SIZE );

	memcpy( APP_Tx_Buffer, Buf, Len );

	usbd_cdc_TxStart( len );
		return -1;

	return len;
}

uint32_t VCP_DataRxLength()
{
	return APP_Rx_length;
}

void VCP_RxFlush()
{
	APP_Rx_length = 0;
}

uint8_t* VCP_RxBuffer()
{
	return APP_Rx_Buffer;
}

/**
 * @brief  VCP_DataRx
 *         Data received over USB OUT endpoint are sent over CDC interface
 *         through this function.
 *
 *         @note
 *         This function will block any OUT packet reception on USB endpoint
 *         until exiting this function. If you exit this function before transfer
 *         is complete on CDC interface (ie. using DMA controller) it will result
 *         in receiving more data while previous ones are still not sent.
 *
 * @param  Buf: Buffer of data to be received
 * @param  Len: Number of data received (in bytes)
 * @retval Result of the opeartion: USBD_OK if all operations are OK else VCP_FAIL
 */
static uint16_t VCP_DataRx(uint8_t* Buf, uint32_t Len)
{
	int len = min( Len, APP_RX_DATA_SIZE - APP_Rx_length );
	if( len <= 0 )
		return -1;

	memcpy( APP_Rx_Buffer + APP_Rx_length, Buf, len );
	APP_Rx_length += len;

	return USBD_OK;
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
