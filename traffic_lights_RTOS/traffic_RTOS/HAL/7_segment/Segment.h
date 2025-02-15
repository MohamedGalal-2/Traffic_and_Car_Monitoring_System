/*
 * Segment.h
 *
 *  Created on: Feb 6, 2025
 *      Author: mokhtar
 */

#ifndef _SEGMENT_SEGMENT_H_
#define _SEGMENT_SEGMENT_H_

#include "stander_file.h"

typedef enum {
    seg_common_anode,
    seg_common_cathod
}seg_status_t;
typedef enum {
    segment_intialize_0 ,
    segment_intialize_1 ,
    segment_intialize_2 ,
    segment_intialize_3
}segment_number;


typedef struct {
	GPIO_TypeDef *led_port[4];
	uint16_t led_pin[4];
	seg_status_t seg_status;
}segment_type;

void segment_wright_logic(const segment_type *segment , uint8_t number);

#endif /* 7_SEGMENT_SEGMENT_H_ */
