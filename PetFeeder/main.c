/*
* PetFeeder.c
*
* Author: Jeremy Butler
* Created: 08-Aug-2013 3:52:41 PM
* Last Updated: 26-Nov-2013
* 
*/
#define F_CPU 1200000

//#define _SHIFT_TEST
//#define _BUTTON_TEST
#define _LCD_TEST

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "74hc959.h"

/*
--Port B connections--
Pins 3 and 4 are connected to the motor driver.
Pin 0 is connected to the LED.
Pin 1 is connect to the button.
*/
#define LED PB0
#define BUTTON PB1

//Global Variables////////////////////////////////////////////////////////////////////////
#ifdef _BUTTON_TEST
static volatile uint8_t ButtonCount = 0;

#elif defined(_SHIFT_TEST)
uint8_t Zero = 0;

#elif defined(_LCD_TEST)

#endif
//////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	
	//Set up interrupts////////////////////////////////////////////////////////////////////////
	cli(); //disable global interrupts
	
	#ifdef _BUTTON_TEST
	TCCR0A |= 1<<WGM01; //Timer in CTC mode
	TCCR0B |= (1 << CS01) | (1 << CS00); //Prescaler to clk/64
	OCR0A = 94; //Compare Register. 94 with prescaler of 64 is about 5 milliseconds
	TIMSK0 |= 1 << OCIE0A; //Enable Compare Match A Interrupt
	
	#elif defined(_SHIFT_TEST)
	asm volatile ("nop");
	
	#elif defined(_LCD_TEST)
	asm volatile ("nop");
	
	#endif
	
	sei(); //enable gloabl interrupts
	///////////////////////////////////////////////////////////////////////////////////////////
	
	
	//Set up port defintions///////////////////////////////////////////////////////////////////
	#ifdef _BUTTON_TEST
	DDRB = (1<<DDB4)|(1<<DDB3)|(1<<DDB0);//Pins 0, 3, and 4 are outputs. All others are inputs.
	PORTB = (1<<BUTTON);//Give button a pull-up resistor
	
	#elif defined(_SHIFT_TEST)
	DDRB = 0xFF; // All pins are outputs
	PORTB = 0x00;
	
	#elif defined(_LCD_TEST)
	DDRB = 0xFF; // All pins are outputs
	PORTB = 0x00; // Set all pins low
	
	#endif
	///////////////////////////////////////////////////////////////////////////////////////////
	
	//Set up local variables///////////////////////////////////////////////////////////////////
	#ifdef _BUTTON_TEST
	
	#elif defined(_SHIFT_TEST)
	
	#elif defined(_LCD_TEST)
	static uint8_t command = 0;
	#endif
	///////////////////////////////////////////////////////////////////////////////////////////
	
	#ifdef _BUTTON_TEST
	
	#elif defined(_SHIFT_TEST)
	
	#elif defined(_LCD_TEST)
	
	#endif
	while(1)
	{
		#ifdef _BUTTON_TEST
		if(ButtonCount >= 6)
		{
			ButtonCount = 0;
			PORTB ^= (1<<LED);
		}
		
		#elif defined(_SHIFT_TEST)
		static uint8_t counter = 0;
		counter++;  // Counter used for displaying a number in binary via the shift register
		shift_out(&counter);  // PB1 = SERCLK  PB2 = RCLK  PB3 = SER
		_delay_ms(500);
		shift_out(&Zero);  // Set all pins low
		_delay_ms(500);
		
		#elif defined(_LCD_TEST)
		
		
		#endif
	}
}

//Interrupt Service Routines///////////////////////////////////////////////////////////////////
#ifdef _BUTTON_TEST
//The INT0 Interrupt Service Routine
ISR(INT0_vect)
{
	if(PINB & (1<<PINB1)) //Check if button is pressed
	{
		//Button is not pressed
		PORTB &= ~((1<<PB3)|(1<<PB0)); //Turn off motor and LED
	}
	else
	{
		//Button is pressed
		PORTB |= (1<<PB3)|(1<<PB0); //Turn on motor and LED
	}
}

void debounce()
{
	static uint8_t state = 0; // Current Debounce State
	
	state = (state<<1) | ((PINB & (1 << BUTTON)) >> BUTTON) | 0xe0;
	if(state == 0xf0)
	{
		ButtonCount++;
	}
}

ISR(TIM0_COMPA_vect)
{
	debounce();
}

#elif defined(_SHIFT_TEST)

#elif defined(_LCD_TEST)

#endif
///////////////////////////////////////////////////////////////////////////////////////////
