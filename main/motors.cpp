#include "motors.h"

Encoder EncA(encA1, encA2);
Encoder EncB(encB1, encB2);
Encoder EncC(encC1, encC2);

void setup_motors() {
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enC, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);

  //set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  analogWrite(enC, 200);
}

/*
 * Moves all 3 actuators a corresponding pos up or down.
 * Moves up if pos > 0, and down otherwise.
 * 
 * pos: threshold value to check from the encoders
 */
void move_effector(long pos) {
  // up
  if (pos > 0) {
    // switch on all the motors
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(in5, HIGH);
    digitalWrite(in6, LOW);
    // while any actuator has not reached the threshold
    while (EncA.read() < pos || EncB.read() < pos || EncC.read() < pos) {
      if (EncA.read() >= pos) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
      }
      if (EncB.read() >= pos) {
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
      }
      if (EncC.read() >= pos) {
        digitalWrite(in5, LOW);
        digitalWrite(in6, LOW);
      }
    }
  } else { //down
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(in5, LOW);
    digitalWrite(in6, HIGH);
    while (EncA.read() > pos || EncB.read() > pos || EncC.read() > pos) {
      if (EncA.read() <= pos) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
      }
      if (EncB.read() <= pos) {
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
      }
      if (EncC.read() <= pos) {
        digitalWrite(in5, LOW);
        digitalWrite(in6, LOW);
      }
    }
  }
  turn_off();
  
}

/*
 * updates the current position of an actuator 
 * using the value from its corresponding encoder
 * 
 * &oldPosition : pointer to current position
 * &enc : pointer to corresponding encoder
 * 
 * returns : a boolean value depending on whether
 *            the position was updated
 */
int update_pos_single(long *oldPosition, Encoder* enc) {
  long newPosition = enc->read();
  if (*oldPosition == newPosition)
    return 0;
  *oldPosition = newPosition;
  return 1;
}

void print_diff_pos(long *posA, long *posB, long *posC) {
  // Check if any position was updated
  if (!update_pos_single(posA, &EncA) ||
      !update_pos_single(posB, &EncB) ||
      !update_pos_single(posC, &EncC)) 
    return;
  
  Serial.print("A:");
  Serial.println(*posA);
  Serial.print("B:");
  Serial.println(*posB);
  Serial.print("C:");
  Serial.println(*posC);
}

/*
 * moves a single actuator 
 * 
 * &enc : pointer to corresponding encoder
 * pos: threshold value to check from the encoders
 * in1 : first pin value for the motor
 * in2 : second pin value for the motor
 */
void move_single(Encoder* enc, long pos, int in1, int in2) {
  // move up
  if (pos > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    while (enc->read() < pos);
  } else { // move down
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    while (enc->read() > pos);
  }
  turn_off();
}

/*
 * Functions: move_A, move_B, move_C
 * 
 * move their corresponding actuators
 */
void move_A(long pos) {
  move_single(&EncA, pos, in1, in2);
}

void move_B(long pos) {
  move_single(&EncB, pos, in3, in4);
}

void move_C(long pos) {
  move_single(&EncC, pos, in5, in6);
}

/*
 * Functions: move_to_A, move_to_B, move_to_C
 * 
 * moves the effector to the corresponding actuator
 * by moving the other two actuators up (if pos > 0)
 * or down otherwise
 * 
 * pos: threshold value to check from the encoders
 */
void move_to_A(long pos) {
  move_B(pos);
  move_C(pos);
}

void move_to_B(long pos) {
  move_A(pos);
  move_C(pos);
}

void move_to_C(long pos) {
  move_A(pos);
  move_B(pos);
}

void move_hex(long pos) {
  move_to_A(pos);
  move_B(-pos);
  move_A(pos);
  move_C(-pos);
  move_B(pos);
  move_A(-pos);
  move_C(pos);
  move_to_A(-pos);
}

/*
 * turns off all output pins to motors
 */
void turn_off() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
}

/*
 * resets encoder values to 0
 */
void reset_enc() {
  EncA.write(0);
  EncB.write(0);
  EncC.write(0);
}

/*
 * movement test for A, B, C, in that order.
 * can be used to determine A, B, C.
 */
void test_move(long pos) {
  move_A(pos);
  move_A(-pos);
  move_B(pos);
  move_B(-pos);
  move_C(pos0);
  move_C(-pos);
  move_to_A(pos);
  move_to_A(-pos);
  move_to_B(pos);
  move_to_B(-pos);
  move_to_C(pos);
  move_to_C(-pos);
  move_hex(pos);
  turn_off();
}