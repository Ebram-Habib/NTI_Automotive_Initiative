/*
 * LCD_int.h
 *
 *  Created on: Oct 23, 2023
 *      Author: Ebram Habib
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

#include "std_types.h"

void H_LCD_void_Init(void);
void H_LCD_void_sendData(u8 copy_u8data );
void H_LCD_void_sendCommand(u8 copy_u8command);
void H_LCD_void_sendString(const u8 * pstr);
void H_LCD_void_clearDisplay(void);
void H_LCD_void_gotoXY(u8 copy_u8Row,u8 copy_u8Col);
void H_LCD_void_displayCustomChar(u8 copy_u8charLocation);
void H_LCD_void_creatCustomChar(const u8 * ArrPattern,u8 copy_u8charLocation);
void H_LCD_void_displayfloat(f32 copy_f32floatValue);
void H_LCD_void_displayBinary(u8 copy_u8charCode);
void H_LCD_void_displayHex(u8 copy_u8charCode);
void H_LCD_void_sendIntNum(s32 copy_intNum);


#endif /* LCD_INT_H_ */
