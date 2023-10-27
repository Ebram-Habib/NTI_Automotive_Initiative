/*
 * LCD_priv.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Ebram Habib
 */

#ifndef LCD_PRIV_H_
#define LCD_PRIV_H_

#include "std_types.h"

/* Commands Set */
#define LCD_CLEAR							 0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80
#define LCD_SET_CGRAM_ADDRESS				 0X40
#define LCD_SET_DDRAM_ADDRESS				 0X80

static void H_LCD_void_latchByte(u8 copy_u8Byte);

#endif /* LCD_PRIV_H_ */
