#include "../system/config.h"

Stepper::Stepper(int number_of_steps, int pin_clk, int pin_en, int pin_dir)
{
	this->step_number = 0;
	this->direction = 0;
	this->number_of_steps = number_of_steps;

	this->pin_clk = pin_clk;
	this->pin_dir = pin_dir;
	this->pin_en  = pin_en;

//	gpio_pinMode(this->pin_clk, OUTPUT);
	gpio_pinMode(this->pin_dir, OUTPUT);
	gpio_pinMode(this->pin_en, OUTPUT);

	gpio_digitalWrite(this->pin_dir, LOW);
	gpio_digitalWrite(this->pin_en, HIGH);

	ready = 1;
}

//RPM
void Stepper::setSpeed(long rpm)
{

}

void Stepper::stepMotor(void)
{
	static unsigned char first = 1;

	if (first == 1) {
		first = 0;
		gpio_digitalWrite(this->pin_en, LOW);
	}
	if ((--steps_left) == 0) {
		timer_pwm_stop();
		timer_cap_stop();

		stop();
		first = 1;
	}
}

void Stepper::step(int steps_to_move)
{
	steps_left = abs(steps_to_move);

	if (steps_to_move > 0)
		gpio_digitalWrite(this->pin_dir, LOW);
	else
		gpio_digitalWrite(this->pin_dir, HIGH);

	ready = 0;

	timer_pwm_init();
	timer_cap_init();

	timer_cap_start();
	timer_pwm_start();
}

void Stepper::stop(void)
{
	gpio_digitalWrite(this->pin_dir, LOW);
	gpio_digitalWrite(this->pin_en, HIGH);

	ready = 1;
}
