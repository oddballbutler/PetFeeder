/*
 * PetFeeder.c
 *
 * Created: 11/8/2013 3:52:41 PM
 *  Author: Jeremy Butler
 */ 



#include <avr/io.h>
#include <avr/interrupt.h>

/*
--Port B connections--
Pins 3 and 4 are connected to the motor driver.
Pin 0 is connected to the LED.
Pin 1 is connect to the button.
*/
#define LED PB0
#define BUTTON PB1

static volatile uint8_t ButtonCount = 0;

int main(void)
{
	//Set up interrupts////////////////////////////////////////////////////////////////////////
	cli(); //disable global interrupts
	
	//GIMSK |= 1<<INT0; //Enable pin 1 as interrupt pin INT0
	
	//Set the MCU Control Register so that any logic change on INT0 will generate and interrupt
	//MCUCR &= ~(1<<ISC01); //Clear the ISC01 bit
	//MCUCR |= (1<<ISC00); //Set the ISC00 bit
	
	TCCR0A |= 1<<WGM01; //Timer in CTC mode
	TCCR0B |= (1 << CS01) | (1 << CS00); //Prescaler to clk/64
	OCR0A = 94; //Compare Register. 94 with prescaler of 64 is about 5 milliseconds
	TIMSK0 |= 1 << OCIE0A; //Enable Compare Match A Interrupt
	
	
	sei(); //enable gloabl interrupts
	///////////////////////////////////////////////////////////////////////////////////////////
	
	//Set up port directions///////////////////////////////////////////////////////////////////
	PORTB = (1<<BUTTON);//Give button a pull-up resistor
	DDRB = (1<<DDB4)|(1<<DDB3)|(1<<DDB0);//Pins 0, 3, and 4 are outputs. All others are inputs.
	///////////////////////////////////////////////////////////////////////////////////////////
	
    while(1)
    {
		if(ButtonCount >= 6)
		{
			ButtonCount = 0;
			PORTB ^= (1<<LED);
		}
    }
}

//The INT0 Interrupt Service Routine
//ISR(INT0_vect)
//{
	//if(PINB & (1<<PINB1)) //Check if button is pressed
	//{
		////Button is not pressed
		//PORTB &= ~((1<<PB3)|(1<<PB0)); //Turn off motor and LED
	//}
	//else
	//{
		////Button is pressed
		//PORTB |= (1<<PB3)|(1<<PB0); //Turn on motor and LED
	//}
//}

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
//
