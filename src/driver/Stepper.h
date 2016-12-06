#ifndef Stepper_h
#define Stepper_h

class Stepper {
  public:
    Stepper(int number_of_steps, int pin_clk, int pin_en, int pin_dir);

    void setSpeed(long whatSpeed);

    void step(int number_of_steps);

    void stepMotor(void);

    void stop(void);

	int steps_left;

	int ready;

  private:
    int direction;
    int number_of_steps;
    int step_number;

    int pin_clk;
    int pin_dir;
    int pin_en;
};

#endif

