/**
 ******************************************************************************
 * @file    usart_hal.h
 * @author  Satish Nair, Brett Walach
 * @version V1.0.0
 * @date    12-Sept-2014
 * @brief
 ******************************************************************************
  Copyright (c) 2013-2015 Particle Industries, Inc.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_HAL_H
#define __USART_HAL_H

#include <stdbool.h>

/* Includes ------------------------------------------------------------------*/
#include "pinmap_hal.h"

/* Exported defines ----------------------------------------------------------*/
#if PLATFORM_ID == 10 // Electron
	#define TOTAL_USARTS		5
#else
	#define TOTAL_USARTS		2
#endif
#define SERIAL_BUFFER_SIZE      64

// Available Serial Configurations for C
#define SERIAL_8N1 (uint8_t)0b00000000
#define SERIAL_8N2 (uint8_t)0b00000001
#define SERIAL_8E1 (uint8_t)0b00000100
#define SERIAL_8E2 (uint8_t)0b00000101
#define SERIAL_8O1 (uint8_t)0b00001000
#define SERIAL_8O2 (uint8_t)0b00001001
#define SERIAL_9N1 (uint8_t)0b00010000
#define SERIAL_9N2 (uint8_t)0b00010001

// Serial Configuration masks
#define SERIAL_VALID_CONFIG (uint8_t)0b00001100
#define SERIAL_STOP_BITS (uint8_t)0b00000011
#define SERIAL_PARITY_BITS (uint8_t)0b00001100
#define SERIAL_NINE_BITS (uint8_t)0b00010000
#define SERIAL_FLOW_CONTROL ((uint8_t)0b01100000)

// Flow control settings
#define SERIAL_FLOW_CONTROL_NONE ((uint8_t)0b00000000)
#define SERIAL_FLOW_CONTROL_RTS ((uint8_t)0b00100000)
#define SERIAL_FLOW_CONTROL_CTS ((uint8_t)0b01000000)
#define SERIAL_FLOW_CONTROL_RTS_CTS ((uint8_t)0b01100000)

// LIN Configuration masks
#define LIN_MODE ((uint32_t)0x0300)
#define LIN_BREAK_BITS ((uint32_t)0x0C00)

// LIN modes
#define LIN_MODE_MASTER ((uint32_t)0x0100)
#define LIN_MODE_SLAVE  ((uint32_t)0x0200)

// LIN break settings
// Supported only in Master mode
#define LIN_BREAK_13B ((uint32_t)0x0000)
// Supported only in Slave mode
#define LIN_BREAK_10B ((uint32_t)0x0800)
#define LIN_BREAK_11B ((uint32_t)0x0C00)

// Pre-defined LIN configurations
#define LIN_MASTER_13B (uint32_t)(((uint32_t)SERIAL_8N1) | LIN_MODE_MASTER | LIN_BREAK_13B)
#define LIN_SLAVE_10B  (uint32_t)(((uint32_t)SERIAL_8N1) | LIN_MODE_SLAVE  | LIN_BREAK_10B)
#define LIN_SLAVE_11B  (uint32_t)(((uint32_t)SERIAL_8N1) | LIN_MODE_SLAVE  | LIN_BREAK_11B)


/* Exported types ------------------------------------------------------------*/
typedef struct Ring_Buffer
{
  uint16_t buffer[SERIAL_BUFFER_SIZE];
  volatile uint16_t head;
  volatile uint16_t tail;
} Ring_Buffer;

typedef enum HAL_USART_Serial {
  HAL_USART_SERIAL1 = 0,    //maps to USART_TX_RX
  HAL_USART_SERIAL2 = 1     //maps to USART_RGBG_RGBB
#if PLATFORM_ID == 10 // Electron
  ,HAL_USART_SERIAL3 = 2    //maps to USART_TXD_UC_RXD_UC
  ,HAL_USART_SERIAL4 = 3    //maps to USART_C3_C2
  ,HAL_USART_SERIAL5 = 4    //maps to USART_C1_C0
#endif
} HAL_USART_Serial;

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

void HAL_USART_Init(HAL_USART_Serial serial, Ring_Buffer *rx_buffer, Ring_Buffer *tx_buffer);
void HAL_USART_Begin(HAL_USART_Serial serial, uint32_t baud);
void HAL_USART_End(HAL_USART_Serial serial);
uint32_t HAL_USART_Write_Data(HAL_USART_Serial serial, uint8_t data);
int32_t HAL_USART_Available_Data_For_Write(HAL_USART_Serial serial);
int32_t HAL_USART_Available_Data(HAL_USART_Serial serial);
int32_t HAL_USART_Read_Data(HAL_USART_Serial serial);
int32_t HAL_USART_Peek_Data(HAL_USART_Serial serial);
void HAL_USART_Flush_Data(HAL_USART_Serial serial);
bool HAL_USART_Is_Enabled(HAL_USART_Serial serial);
void HAL_USART_Half_Duplex(HAL_USART_Serial serial, bool Enable);
void HAL_USART_BeginConfig(HAL_USART_Serial serial, uint32_t baud, uint32_t config, void*);
uint32_t HAL_USART_Write_NineBitData(HAL_USART_Serial serial, uint16_t data);
void HAL_USART_Send_Break(HAL_USART_Serial serial, void* reserved);
uint8_t HAL_USART_Break_Detected(HAL_USART_Serial serial);

#ifdef __cplusplus
}
#endif

#endif  /* __USART_HAL_H */
