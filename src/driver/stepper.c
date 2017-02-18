#include <msp430g2553.h>

unsigned char stepper_ready = 0;
unsigned int stepper_location = 0;

static unsigned int steps_left = 0;
static unsigned char stepper_direction = 1;

const static unsigned int max_of_steps = 6400;
const static unsigned char stepper_mask[4] = {0x03, 0x06, 0x0c, 0x09};

void stepper_init(void)
{
	P2DIR = 0x0f;
	P2OUT = 0x00;

	TA0CCR0 = 5000;
	TA0CCTL0 = CCIE;
	TA0CTL = TASSEL_2 + ID_3 + MC_0 + TACLR;

	stepper_ready = 1;
}

void stepper_step(int steps_to_move)
{
//	stepper_location =
	steps_left = abs(steps_to_move);

	if (steps_to_move > 0) {stepper_direction = 1;}
	if (steps_to_move < 0) {stepper_direction = 0;}

	stepper_ready = 0;

	TA0CTL |= MC_1;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void stepper_timer_isr(void)
{
	if (steps_left > 0) {
		if (stepper_direction == 1) {
			stepper_location++;
			if (stepper_location == max_of_steps) {
				steps_left = 0;
			}
		}
		else {
			stepper_location--;
			if (stepper_location == 0) {
				steps_left = 0;
			}
		}
		steps_left--;

		P2OUT = stepper_mask[stepper_location % 4];
	}
	else {
		stepper_init();
	}
}
