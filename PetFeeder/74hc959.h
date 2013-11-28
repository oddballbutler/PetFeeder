/************************************************************************/
/* 74hc595.h
/* Author: Jeremy Butler
/* Date: 26-Aug-2013
/*
/* These functions allow easy use of the 74HC595 output shift register
/* in microcontroller programs. Make sure to modify the definitions in
/* this file to fit your hardware needs.
/*
/************************************************************************/

#ifndef _74HC595_H_
#define _74HC595_H_

#include <avr/io.h>
#include "avr_helper.h"

/************************************************************************/
/* !!!MODIFY THESE DEFINITIONS DEPENDING ON YOUR HARDWARE!!!            */
/************************************************************************/
#define NUM_REG 1 //How many of the shift registers are there daisy-chained?

//#define _SRCLR_CONNECTED //Uncomment this line if the SRCLR pin is connected to your microcontroller.

#define SRCLK_HIGH_74HC595() SETBIT(PORTB,PB0)  //Set the shift register clock pin high
#define SRCLK_LOW_74HC595() CLEARBIT(PORTB,PB0) //Set the shift register clock pin low

#define SER_HIGH_74HC595() SETBIT(PORTB,PB1)  //Set the serial line high
#define SER_LOW_74HC595() CLEARBIT(PORTB,PB1) //Set the serial line low
#define WRITE_SER_74HC595(RADDRESS,RBIT) WRITEBIT(RADDRESS,RBIT,PORTB,PB1) //Write a bit of a byte to the serial line

#define RCLK_HIGH_74HC595() SETBIT(PORTB,PB2)  //Set the storage register clock pin high
#define RCLK_LOW_74HC595() CLEARBIT(PORTB,PB2) //Set the storage register clock pin low

//These should only be defined if the SRCLR pin is connected to the microcontroller.
#ifdef _SRCLR_CONNECTED
#define SRCLR_HIGH_74HC595() SETBIT(PORTB,PB3)  // Set the Shift Register Clear pin high
#define SRCLR_LOW_74HC595() CLEARBIT(PORTB,PB3) // Set the Shift Register Clear pin low
#endif // _SRCLR_CONNECTED

/************************************************************************/
/* !!!DO NOT MODIFY ANYTHING BEYOND THIS POINT!!!                       */
/************************************************************************/

/************************************************************************/
/* Sample Test Program                                                  */
/************************************************************************/
/*
int main(){
	DDRB = 0xFF;
	PORTB = 0x00;
	uint8_t counter = 0;

	while(1){
		counter++;  // Counter used for displaying a number in binary via the shift register
		shift_out(&counter);  // PB1 = SERCLK  PB2 = RCLK  PB3 = SER
		_delay_ms(500);
		clear_shift_register();  // Set all pins low
		_delay_ms(500);
	}
	return 0;
}
/*

/************************************************************************/
/* Function Prototypes                                                  */
/************************************************************************/

/**
 * \brief This is a FIFO shift register function.
 * 
 * \param data_p A pointer to the byte array that you wish to output onto the shift registers.
 * 
 * \return void
 */
void shift_out(uint8_t * data_p);

#ifdef _SRCLR_CONNECTED
/**
 * \brief Clears the shift register. This is faster than shifting out all zeros.
 * 
 * 
 * \return void
 */
void clear_shift_register();
#endif // _SRCLR_CONNECTED

#endif // _74HC595_H_
