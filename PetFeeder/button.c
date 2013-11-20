/************************************************************************/
/* button.c
/************************************************************************/

//Button Functions
void initialize_button(Button * button, uint8_t port, uint8_t pin){
	button->port = port;
	button->pin = pin;
	button->state = 1;
}

uint8_t read_button(Button * button)
{
	return ((_SFR_IO8(button->port)) & (button->pin)) >> button->pin;
}

uint8_t debounce_read(Button * button)
{
	uint8_t debounce_state = 0;
	debounce_state = (debounce_state << 1) | !read_button(button) | 0xe0;
	if (debounce_state == 0xf0)
	{
		return 1;
	} 
	return 0;
}

#endif /* _BUTTON_H_ */