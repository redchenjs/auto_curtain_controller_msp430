#include <msp430g2553.h>
#include "../driver/stepper.h"

unsigned char stepper_ready = 0;
unsigned int stepper_location = 0;

static unsigned int location_set = 0;

const static unsigned char stepper_mask[4] = {0x03, 0x06, 0x0c, 0x09};

void stepper_step(unsigned int steps_to_move, unsigned char direction)
{
	const static unsigned int min_of_steps = 0;
	const static unsigned int max_of_steps = 6400;

	if (direction == FORWARD) {
		if (steps_to_move + location_set > max_of_steps) {
			location_set = max_of_steps;
		}
		else {
			location_set += steps_to_move;
		}
	}
	else {
		if (steps_to_move > location_set) {
			location_set = min_of_steps;
		}
		else {
			location_set -= steps_to_move;
		}
	}

	stepper_ready = 0;

	TA0CTL |= MC_1;
}

void stepper_init(void)
{
	P2DIR = 0x0f;
	P2OUT = 0x00;

	TA0CCR0 = 5000;
	TA0CCTL0 = CCIE;
	TA0CTL = TASSEL_2 + ID_3 + MC_0 + TACLR;

	stepper_ready = 1;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void stepper_timer_isr(void)
{
	if (stepper_location != location_set) {
		if (stepper_location < location_set) {
			stepper_location++;
		}
		else {
			stepper_location--;
		}
		P2OUT = stepper_mask[stepper_location % 4];
	}
	else {
		stepper_init();
	}
}
