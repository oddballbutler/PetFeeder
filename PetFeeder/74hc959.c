/************************************************************************/
/* 74hc595.c
/* Author: Jeremy Butler
/* Date: 26-Aug-2013
/*
/* See 74hc959.h for documentation.
/*
/************************************************************************/
#include "74hc959.h"

void shift_out(uint8_t * data_p)
{
	uint8_t i;
	int8_t j;
	RCLK_LOW_74HC595();  // Set the storage register clock pin low

	for (i = 0; i < NUM_REG; i++)
	{	// Now we are entering the loop to shift out 8+ bits
		uint8_t data = data_p[i];
		for (j = 7; j >= 0; j--)
		{
			SRCLK_LOW_74HC595();  // Set the shift register clock pin low
			WRITE_SER_74HC595(data,j);  // Output the next bit onto the serial pin
			SRCLK_HIGH_74HC595(); // Set the shift register clock pin high
		}

	}

	RCLK_HIGH_74HC595();  // Set the register-clock pin high to update the output of the shift-register
}

#ifdef _SRCLR_CONNECTED
void clear_shift_register()
{
	RCLK_LOW_74HC595();  // Set the storage register clock pin low
	SRCLR_LOW_74HC595(); // Set the shift register clear pin low
	RCLK_HIGH_74HC595(); // Set the storage register clock pin high
	SRCLR_HIGH_74HC595(); // Set the shift register clear pin high
}
#endif // _SRCLR_CONNECTED
