#ifndef MOTORS_H
#define MOTORS_H

//#include "Arduino.h"
#include <Encoder.h>

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
void move_effector(long);
/* updates the position of a single encoder */
int update_pos_single(long*, Encoder*);
/* prints the position of all encoders, if change is detected */
void print_diff_pos();
/* moves a single actuator */
void move_single(Encoder*, long, int, int);
/* moves actuator A, B, C */
void move_A(long);
void move_B(long);
void move_C(long);
/* moves effector away from corresponding actuator */
void move_from_A(long);
void move_from_B(long);
void move_from_C(long);
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
/* test movement of A, B, C, in that order */
void test_move(long);

#endif
