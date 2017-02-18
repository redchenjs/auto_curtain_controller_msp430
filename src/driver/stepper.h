#ifndef STEPPER_H_
#define STEPPER_H_

extern unsigned char stepper_ready;
extern unsigned int stepper_location;

extern void stepper_init(void);
extern void stepper_step(int steps_to_move);

#endif
