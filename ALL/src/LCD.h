/*
 * LCD.h
 *
 * Created: 10.02.2018 12:13:39
 *  Author: bartek
 */ 


#ifndef LCD_H_
#define LCD_H_

//--------I2C definitions-------
//#define I2C_COMMAND 0x70
//#define I2C_DATA 0x72
#define I2C_COMMAND 0x78>>1
#define I2C_DATA 0x7A>>1
#define LCD_SET_COLUMN_ADDR_LSB 0x00
#define LCD_SET_COLUMN_ADDR_MSB 0x10
#define LCD_SET_POWER_CTRL 0x28
#define LCD_SET_LINE_ADDR 0x40
#define LCD_SET_PAGE_ADDR 0xB0
#define LCD_SET_BIAS 0x81
#define LCD_ENABLE_DISPLAY 0xAF
#define LCD_ENABLE_ALL 0xA5
#define LCD_INVERT_DISPLAY 0xA7
#define LCD_SYSTEM_RESET 0xE2
#define LCD_SET_SCROLL 0x88

#define CHAR_LARROW 127
#define CHAR_RARROW 126
#define CHAR_DEG 128

void LCDcommand(uint8_t command);


void LCDcommand2(uint8_t command, uint8_t val);
void LCDdata(char data);
void LCDgoto(unsigned char row, unsigned char col);
void LCDhome(void);
void LCDnewline(void);
void LCDclear2end(void);
void LCDclearline(unsigned char l);
void LCDclear(void);
void LCDtext(char* text);
void LCDwrite(unsigned char c);
void LCDchar(uint16_t c);
void LCDspecial5x8(char c);
void LCDspecial8x8(char c);
void LCDdrawButtons(void);
void LCDinit(void);
void LCD_printFloat(float val);
#endif /* LCD_H_ */
