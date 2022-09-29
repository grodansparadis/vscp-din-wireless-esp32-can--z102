/*
 * This file is part of the WiCAN project.
 *
 * Copyright (C) 2022  Meatpi Electronics.
 * Original written by Ali Slim <ali@meatpi.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __CAN4VSCP_H__
#define __CAN4VSCP_H__

#include "driver/twai.h"

#define CAN4VSCP_5K				        0   /**< TWAI bus-speed 5K */
#define CAN4VSCP_10K				      1   /**< TWAI bus-speed 10K */
#define CAN4VSCP_20K				      2   /**< TWAI bus-speed 20K */
#define CAN4VSCP_25K				      3   /**< TWAI bus-speed 25K */
#define CAN4VSCP_50K				      4   /**< TWAI bus-speed 50K */
#define CAN4VSCP_100K			        5   /**< TWAI bus-speed 100K */
#define CAN4VSCP_125K			        6   /**< TWAI bus-speed 125K CAN4VSCP speed */
#define CAN4VSCP_250K			        7   /**< TWAI bus-speed 250K */
#define CAN4VSCP_500K			        8   /**< TWAI bus-speed 500K */
#define CAN4VSCP_800K			        9   /**< TWAI bus-speed 800K */
#define CAN4VSCP_1000K			     10   /**< TWAI bus-speed 1M */
#define CAN4VSCP_AUTO            99   /**< TWAI autodetect speed */

/**!
 * @brief TWAI bus speed structure
 */
typedef struct {
	uint8_t bus_state;    /**< State of the bus */
	uint8_t silent;       /**< Silent mode */
	uint8_t loopback;     /**< Loopback mode */
	uint16_t brp;         /**< Bitrate */
	uint8_t phase_seg1;   /**< Phase segment 1 */
	uint8_t phase_seg2;   /**< Phase segment 2 */
	uint8_t sjw;          /**< SJW */
	uint32_t filter;      /**< Message filter */
	uint32_t mask;        /**< Message mask */
} can4vscp_cfg_t;       


/*!
  @fn can4vscp_block
  @brief Block transmission/reception
*/
void
can4vscp_block(void);

/*!
  @fn can4vscp_unblock
  @brief Unblock transmission/reception
*/
void
can4vscp_unblock(void);

/*!
  @fn can4vscp_enable
  @brief Enable TWAI
  Filtering is set so all TWAI messages are received.
*/
void can4vscp_enable(void);

/*!
  @fn can4vscp_disable
  @brief Disable TWAI  
*/
void can4vscp_disable(void);

/*!
  @fn can4vscp_setSilent
  @brief Handle silent mode
  I/f must be disabled to set/reset silent mode
  @param flag Set to 1 for silent, 0 for active.
*/
void can4vscp_setSilent(uint8_t flag);

/*!
  @fn can4vscp_isSilent
  @brief Check if CAN i/f is silent
  @return true if enabled
*/
uint8_t can4vscp_isSilent(void);

/*!
  @fn can4vscp_setLoopback
  @brief Handle loopback mode
  I/f must be disabled to set/reset silent mode
  @param flag Set to 1 for loopback, 0 for normal mode.
*/
void can4vscp_setLoopback(uint8_t flag);

/*!
  @fn can4vscp_isLoopback
  @brief Check if CAN i/f is in loopback mode
  @return true if enabled
*/
uint8_t can4vscp_isLoopback(void);

/*!
  @fn can4vscp_setFilter
  @brief Set filter
  I/f must be disabled to set filter.
  @param filter 32-bit filter value to set
*/
void can4vscp_setFilter(uint32_t filter);

/*!
  @fn can4vscp_setMask
  @brief Set mask
  I/f must be disabled to set mask.
  @param mask 32-bit mask value to set
*/
void can4vscp_setMask(uint32_t mask);

/*!
  @fn can4vscp_setBitrate
  @brief Set bitrate for TWAI bus
  I/f must be disabled to set bitrate.
  @param rate Code for bitrate
*/
void can4vscp_setBitrate(uint8_t rate);

/*!
  @fn can4vscp_getBitrate
  @brief Get bitrate for TWAI bus
  @return Code for set bitrate
*/
uint8_t can4vscp_getBitrate(void);

/*!
  @fn can4vscp_init
  @brief Initialize the TWAI interface
  @param bitrate to use
*/
void can4vscp_init(uint8_t bitrate);

/*!
  @fn can4vscp_receive
  @brief Receive TWAI message w/ auto bauderate
  
  @param message Pointer to message that will get receive data
  @param ticks_to_wait Timeout 
  @return ESP_OK if all is OK else error code.
*/
esp_err_t can4vscp_receive(twai_message_t *message, TickType_t ticks_to_wait);

/*!
  @fn can4vscp_send
  @brief Send TWAI message
  
  @param message Pointer to message that will be sent
  @param ticks_to_wait Timeout 
  @return ESP_OK if all is OK else error code.
*/
esp_err_t can4vscp_send(twai_message_t *message, TickType_t ticks_to_wait);

/*!
  @fn can4vscp_isEnabled
  @brief Check if CAN is enabled
  @return true if enabled
*/
bool can4vscp_isEnabled(void);

/*!
  @fn can4vscp_get_bitrate
  @brief Get Bitrate
  @return Code for set bitrate
*/
uint8_t can4vscp_get_bitrate(void);

/*!
  @fn can4vscp_getRxMsgCount
  @brief Get receive message queue count

  @return Receive Queue count
*/
uint32_t can4vscp_getRxMsgCount(void);



// ----------------------------------------------------------------------------
//                                     Tasks
// ----------------------------------------------------------------------------



/*!
  Task that handle receive of messages and fills the 
  rx buffer. The message broker task is informed about
  the received message so it is sent to all other tasks
  @param arg CAN4VSCP context
*/
void twai_receive_task(void *arg);

/*!
  Task that handle trasmit of messages from the
  CAN4VSCP tx buffer.
  @param arg CAN4VSCP context
*/
void twai_transmit_task(void *arg);

#endif