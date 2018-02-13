/*
 * utils.h
 *
 * Created: 10.02.2018 01:03:29
 *  Author: bartek
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define LED_RED_On() PORTR.OUTSET = PIN0_bm
#define LED_RED_Off() PORTR.OUTCLR = PIN0_bm
#define LED_RED_Tgl() PORTR.OUTTGL= PIN0_bm

#define LED_RGB_GREEN_On() PORTE.OUTSET = PIN0_bm
#define LED_RGB_GREEN_Off() PORTE.OUTCLR = PIN0_bm
#define LED_RGB_GREEN_Tgl() PORTE.OUTTGL = PIN0_bm

#define LED_RGB_RED_On() PORTE.OUTSET = PIN1_bm
#define LED_RGB_RED_Off() PORTE.OUTCLR = PIN1_bm
#define LED_RGB_RED_Tgl() PORTE.OUTTGL= PIN1_bm

#define LED_BL_On() PORTD.OUTSET = PIN1_bm
#define LED_BL_Off() PORTD.OUTCLR = PIN1_bm
#define LED_BL_Tgl() PORTD.OUTTGL = PIN1_bm

#endif /* UTILS_H_ */
