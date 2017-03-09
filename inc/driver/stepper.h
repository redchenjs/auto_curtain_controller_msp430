#ifndef STEPPER_H_
#define STEPPER_H_

enum Direction {
    FORWARD  = 0x0,
    BACKWARD = 0x1
};

extern unsigned char stepper_ready;
extern unsigned int stepper_location;

extern void stepper_init(void);
extern void stepper_step(unsigned int steps_to_move, unsigned char direction);

#endif
