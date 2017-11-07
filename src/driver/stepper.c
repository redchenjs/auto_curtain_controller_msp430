#include <msp430.h>
#include "driver/stepper.h"

#define stepper_port P2OUT

unsigned char stepper_ready = 0;

unsigned int stepper_location_now = 0;
unsigned int stepper_location_set = 0;

const static unsigned char stepper_mask[4] = {0x03, 0x06, 0x0c, 0x09};

void stepper_update(void)
{
    stepper_ready = 0;

    TA0CTL |= MC_1;
}

void stepper_step(unsigned int steps_to_move, unsigned char direction)
{
	const static unsigned int min_of_steps = 0;
	const static unsigned int max_of_steps = 2000;

	if (direction == FORWARD) {
		if (steps_to_move + stepper_location_set > max_of_steps) {
			stepper_location_set = max_of_steps;
		}
		else {
			stepper_location_set += steps_to_move;
		}
	}
	else {
		if (steps_to_move > stepper_location_set) {
			stepper_location_set = min_of_steps;
		}
		else {
			stepper_location_set -= steps_to_move;
		}
	}

	stepper_ready = 0;

	TA0CTL |= MC_1;
}

void stepper_init(void)
{
	P2DIR = 0x0f;
	P2OUT = 0x00;

	TA0CCR0   = 4000;
	TA0CCTL0 |= CCIE;
	TA0CTL   |= TASSEL_2 + ID_3 + MC_0 + TACLR;

	stepper_ready = 1;
}

inline void stepper_timer_isr_handle(void)
{
    if (stepper_location_now != stepper_location_set) {
        if (stepper_location_now < stepper_location_set) {
            stepper_location_now++;
        }
        else {
            stepper_location_now--;
        }
        stepper_port = stepper_mask[stepper_location_now & 0x03];
    }
    else {
        TA0CTL |= MC_0;
        stepper_port = 0x00;
        stepper_ready = 1;
    }
}
