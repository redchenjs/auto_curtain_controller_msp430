/*
 * timer.c
 *
 *  Created on: 2016年11月9日
 *      Author: redchenjs
 */

#include "../system/config.h"

#define SET_PWM_PORT	P1DIR |= BIT6; P1SEL |= BIT6
#define SET_CAP_PORT	P2DIR &=~BIT5; P2SEL |= BIT5

extern Stepper motor;

void timer_pwm_init(void)
{
	SET_PWM_PORT;

	TA0CCR0  = 100;								// Period
	TA0CCR1  = 50;								// Duty
	TA0CCTL1 = OUTMOD_7;						// TA0CCR1, Reset/Set
	TA0CTL   = TASSEL_1 + ID_0 + MC_0 + TACLR;	// ACLK, divide 1, upmode, clear TAR
}

void timer_pwm_start(void)
{
	TA0CTL |= MC_1 + TACLR;
}

void timer_pwm_stop(void)
{
	TA0CTL &=~MC_1 + TACLR;
}

void timer_cap_init(void)
{
	SET_CAP_PORT;

	TA1CCTL2 = CAP + SCS + CM_1 + CCIS_1;		// Capture mode, sychronize, posedge, CCIxB
	TA1CTL 	 = TASSEL_2 + ID_0 + MC_2 + TACLR;  // SMCLK, divide 1, Cont Mode, clear TAR
}

void timer_cap_start(void)
{
	TA1CCTL2 |= CCIE;							// interrupt enable
	TA1CTL   |= TACLR + TACLR;
}

void timer_cap_stop(void)
{
	TA1CCTL2 &=~CCIE;							// interrupt disable
}

#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)
{

	switch(__even_in_range(TA1IV,0x0A))
	{
		case  TA1IV_TACCR2:                   // Vector  2:  TACCR1 CCIFG
			TA1CCTL2 &=~CCIFG;
			motor.stepMotor();
			break;
	}

}
