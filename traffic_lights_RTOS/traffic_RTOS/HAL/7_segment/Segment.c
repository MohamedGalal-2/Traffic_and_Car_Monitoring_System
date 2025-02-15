/*
 * Segment.c
 *
 *  Created on: Feb 6, 2025
 *      Author: mokhtar
 */

#include "Segment.h"

void segment_wright_logic(const segment_type *segment , uint8_t number){
	for(int i = 0 ; i < 4 ; i++){
		HAL_GPIO_WritePin((segment->led_port[i]), (segment->led_pin[i]), (number >> i) & 0x01);
	}

}
