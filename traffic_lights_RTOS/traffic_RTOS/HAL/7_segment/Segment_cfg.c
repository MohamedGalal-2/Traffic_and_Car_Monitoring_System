/*
 * Segment_cfg.c
 *
 *  Created on: Feb 6, 2025
 *      Author: mokhtar
 */

#ifndef _SEGMENT_SEGMENT_CFG_C_
#define _SEGMENT_SEGMENT_CFG_C_

#include "Segment_cfg.h"

segment_type segment = {
		.led_port[0] = GPIOB,
		.led_port[1] = GPIOB,
		.led_port[2] = GPIOB,
		.led_port[3] = GPIOB,
		.led_pin[0]  = GPIO_PIN_12,
		.led_pin[1]  = GPIO_PIN_13,
		.led_pin[2]  = GPIO_PIN_14,
		.led_pin[3]  = GPIO_PIN_15,
};

#endif /* 7_SEGMENT_SEGMENT_CFG_C_ */
