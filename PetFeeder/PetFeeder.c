/*
 * PetFeeder.c
 *
 * Created: 11/8/2013 3:52:41 PM
 *  Author: Jeremy Butler
 */ 

/*
--Port B connections--
Pins 3 and 4 are connected to the motor driver.
Pin 0 is connected to the LED.
Pin 1 is connect to the button.
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	//Set up interrupts////////////////////////////////////////////////////////////////////////
	cli(); //disable global interrupts
	
	GIMSK |= 1<<INT0; //Enable pin 1 as interrupt pin INT0
	
	//Set the MCU Control Register so that any logic change on INT0 will generate and interrupt
	MCUCR &= ~(1<<ISC01); //Clear the ISC01 bit
	MCUCR |= (1<<ISC00); //Set the ISC00 bit
	
	sei(); //enable gloabl interrupts
	///////////////////////////////////////////////////////////////////////////////////////////
	
	//Set up port directions///////////////////////////////////////////////////////////////////
	PORTB = (1<<PB1);//Give pin 1 a pull-up resistor
	DDRB = (1<<DDB4)|(1<<DDB3)|(1<<DDB0);//Pins 0, 3, and 4 are outputs. All others are inputs.
	///////////////////////////////////////////////////////////////////////////////////////////
	
    while(1)
    {
        //TODO:: Please write your application code
    }
}

//The INT0 Interrupt Service Routine
ISR(INT0_vect)
{
	bool hello;
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
