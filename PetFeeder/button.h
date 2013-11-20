/************************************************************************/
/* button.h
/************************************************************************/

#ifndef _BUTTON_H_
#define _BUTTON_H_

typedef struct Button
{
	uint8_t port;
	uint8_t pin;
	uint8_t state; //High or low since last poll
	
} Button;

//Button Functions
void initialize_button(Button * button, uint8_t * port, uint8_t pin);
uint8_t raw_read(Button * button);
uint8_t debounce_read(Button * button);

#endif /* _BUTTON_H_ */