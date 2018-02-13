/*
 * LCD.c
 *
 * Created: 10.02.2018 12:13:28
 *  Author: bartek
 */ 

#include <asf.h>
#include "LCD.h"
#include "font.h"
#include "util/delay.h"

unsigned char p_col, p_row;

void LCDcommand(uint8_t command){
	twi_package_t packet_write = {
		.addr[0]      = command,				// TWI slave memory address data
		.addr_length  = 1,						// TWI slave memory address data size
		.chip         = I2C_COMMAND,			// TWI slave bus address
		.length       = 0						// transfer data size (bytes)
	};
	while (twi_master_write(&TWIC, &packet_write) != TWI_SUCCESS);
}

void LCDcommand2(uint8_t command, uint8_t val){
		twi_package_t packet_write = {
			.addr[0]      = command,		// TWI slave memory address data
			.addr[1]	  = val,
			.addr_length  = 2,				// TWI slave memory address data size
			.chip         = I2C_COMMAND,		  // TWI slave bus address
			.length       = 0				// transfer data size (bytes)
		};
		while (twi_master_write(&TWIC, &packet_write) != TWI_SUCCESS);
}

void LCDdata(char data){
	twi_package_t packet_write = {
		.addr[0]      = data,			// TWI slave memory address data
		.addr_length  = 1,				// TWI slave memory address data size
		.chip         = I2C_DATA,	// TWI slave bus address
		.length       = 0				// transfer data size (bytes)
	};
	while (twi_master_write(&TWIC, &packet_write) != TWI_SUCCESS);
}

void LCDgoto(unsigned char row, unsigned char col) {
	LCDcommand(LCD_SET_PAGE_ADDR | (3-row%4));
	LCDcommand(LCD_SET_COLUMN_ADDR_LSB | ( col & 0x0F ));
	LCDcommand(LCD_SET_COLUMN_ADDR_MSB | ( col >> 4 ));

	p_row = row;
	p_col = col;
}

void LCDhome(void) {
	LCDgoto(0, 0);
}

void LCDnewline(void) {
	LCDgoto(p_row == 7 ? 0 : p_row + 1, 0);
}

void LCDclear2end(void) {
	for (; p_col < 128; p_col++) {
		LCDdata(0x00);
	}
}

void LCDclearline(unsigned char l) {
	unsigned char i;

	LCDgoto(l, 0);
	for (i = 0; i < 128; i++) {
		LCDdata(0x00);
	}

	LCDgoto(l, 0);
}

void LCDclear(void) {
	unsigned char row;
	unsigned char col;

	for (row = 0; row < 8; row ++) {
		LCDgoto(row, 0);
		for (col = 0; col < 128; col++) {
			LCDdata(0x00);
		}
	}

	LCDgoto(0, 0);
}

void LCDtext(char* text) {
	while(*text != 0) {
		LCDchar(*text);
		text++;
	}
}

void LCDwrite(unsigned char c) {
	LCDchar(c);
}

void LCDchar(uint16_t c) {
	p_col += 6;
	if (p_col > 122) {
		p_row++;
		if (p_row > 3) {
			p_row = 0;
		}

		LCDgoto(p_row, 0);
	}

	if (c < 32 || c > 140) {
		c = '?';
	}

	c -= 32;

	unsigned char i, j, o, n;
	for(i = 0; i < 5; i++) {
		o = font5x8[5 * c + i];

		for(n = j = 0; j < 8; j++) {
			n = (n << 1) + (o & 1);
			o >>= 1;
		}

		LCDdata(n);
	}

	LCDdata(0x00);
}

void LCDspecial5x8(char c) {
	p_col += 6;
	if (p_col > 122) {
		p_row++;
		if (p_row > 3) {
			p_row = 0;
		}

		LCDgoto(p_row, 0);
	}

	if(c < 0 || c > 128) return;

	unsigned char i, j, o, n;
	for(i = 0; i < 5; i++) {
		o = special5x8[5 * c + i];

		for(n = j = 0; j < 8; j++) {
			n = (n << 1) + (o & 1);
			o >>= 1;
		}

		LCDdata(n);
	}

	LCDdata(0x00);
}

void LCDspecial8x8(char c) {
	p_col += 9;
	if (p_col > 122) {
		p_row++;
		if (p_row > 3) {
			p_row = 0;
		}

		LCDgoto(p_row, 0);
	}

	if(c < 0 || c > 128) return;


	unsigned char i, j, o, n;
	for(i = 0; i < 8; i++) {
		o = special8x8[8 * c + i];

		for(n = j = 0; j < 8; j++) {
			n = (n << 1) + (o & 1);
			o >>= 1;
		}

		LCDdata(n);
	}

	LCDdata(0x00);
}

void LCDdrawButtons(void){
	//ENTER
	LCDgoto(3,1);
	LCDtext("OK");
	//ESC
	LCDgoto(3,40);
	LCDtext("ESC");
	//UP
	LCDgoto(3,83);
	LCDchar(129);
	//DOWN
	LCDgoto(3,115);
	LCDchar(128);
}

void LCDinit(void){
	LCDcommand(LCD_SYSTEM_RESET);
	_delay_ms(10);
	LCDcommand(0xEB);	//bias ratio
	LCDcommand2(LCD_SET_BIAS,220); //bias value
	LCDcommand(LCD_ENABLE_DISPLAY);
	LCDclear();
	LCDgoto(0,0);
	//LCDcommand(0x27);	//temp comp 0.00%/C
	
}

void LCD_printFloat(float val){
	char buffer[12];
	sprintf(buffer, "%+010.2f", val);
	LCDtext(buffer);
}