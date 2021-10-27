#ifndef MOTORS_H
#define MOTORS_H

//#include "Arduino.h"
#include <Encoder.h>
#include "logic.h"

// Motor control pins
// motor A
const int enA = 11;
const int in1 = 12;
const int in2 = 13;
// motor B
const int enB = 10;
const int in3 = 8;
const int in4 = 9;
// motor C
const int enC = 5;
const int in5 = 6;
const int in6 = 7;

// Encoder pins
const int encA1 = 2;
const int encA2 = 3;
const int encB1 = 18;
const int encB2 = 19;
const int encC1 = 20;
const int encC2 = 21;

// Create Encoder objects
extern Encoder EncA;
extern Encoder EncB;
extern Encoder EncC;

/* sets up the motor pins with pinMode */
void setup_motors();
/* moves the effector with all 3 actuators together, given a long */
void move_effector_to(long, long, long);
void move_effector_to(long);
/* moves actuator A, B, C */
void move_A(long);
void move_B(long);
void move_C(long);
/* moves effector toward corresponding actuator */
void move_to_A(long);
void move_to_B(long);
void move_to_C(long);
/* moves in a hexagon */
void move_hex(long);

/* turns off all motors moving actuators */
void turn_off();
/* resets all encoder values to 0 */
void reset_enc();

/* calibrate encoder values */
void calib_enc();
/* get current encoder values */
void get_cur_pos(long[]);

#endif
