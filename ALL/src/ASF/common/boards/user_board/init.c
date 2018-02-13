/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void GPIO_Init(void);
void twi_init(void);

void GPIO_Init(void){
	PORTR.DIRSET = PIN0_bm;	//LED1
	PORTR.OUTCLR = PIN0_bm;
	
	PORTE.DIRSET = PIN0_bm;	//LED2
	PORTE.OUTCLR = PIN0_bm;
	
	PORTE.DIRSET = PIN1_bm;	//LED3
	PORTE.OUTCLR = PIN1_bm;
	
	PORTD.DIRSET = PIN1_bm;	//Backlight
	PORTD.OUTCLR = PIN1_bm;
	
	PORTB.DIRCLR = PIN0_bm;	//SW1
	PORTB.OUTSET = PIN0_bm;
	
	PORTB.DIRCLR = PIN1_bm;	//SW2
	PORTB.OUTSET = PIN1_bm;
	
	PORTB.DIRCLR = PIN2_bm;	//SW3
	PORTB.OUTSET = PIN2_bm;
	
	PORTB.DIRCLR = PIN3_bm;	//SW4
	PORTB.OUTSET = PIN3_bm;
	
}

void twi_init(void){
	twi_options_t opt = {
		.speed = 50000,
	};
	opt.speed_reg = TWI_BAUD(sysclk_get_cpu_hz(), opt.speed);
	
	sysclk_enable_peripheral_clock(&TWIC);
	
	twi_master_init(&TWIC, &opt);
	twi_master_enable(&TWIC);
}



void board_init(void){
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	
	GPIO_Init();
	twi_init();
}

