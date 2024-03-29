/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "utils.h"
#include "LCD.h"
#include <util/delay.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	
	LCDinit();
	//LCDdrawButtons();
	
	//LCDcommand(LCD_SYSTEM_RESET);
	
	LED_BL_On();
	LCDgoto(0,10);
	LCD_printFloat(12.424);
	
	/* Insert application code here, after the board has been initialized. */
	while(1){
		
		LED_RGB_RED_On();
		_delay_ms(100);
		
		LED_RGB_RED_Off();
		_delay_ms(900);
	}
}
