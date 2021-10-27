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
 * Moves all 3 actuators to their determined final positions.
 * 
 * finalPosA : encoder value for A
 * finalPosB : encoder value for B
 * finalPosC : encoder value for C
 */
void move_effector_to(long finalPosA, long finalPosB, long finalPosC) {
  unsigned long prevTime = millis(), curTime = millis();
  finalPosA = check_pos(finalPosA);
  finalPosB = check_pos(finalPosB);
  finalPosC = check_pos(finalPosC);

  long dA = finalPosA - EncA.read();
  long dB = finalPosB - EncB.read();
  long dC = finalPosC - EncC.read();
  bool moreA = dA > 0;
  bool moreB = dB > 0;
  bool moreC = dC > 0;
  bool done = false, doneA = false, doneB = false;
  bool doneC = false, timedOut = false;

  // switch on motors
  digitalWrite(in1, HIGH & moreA);
  digitalWrite(in2, LOW | !moreA);
  digitalWrite(in3, HIGH & moreB);
  digitalWrite(in4, LOW | !moreB);
  digitalWrite(in5, HIGH & moreC);
  digitalWrite(in6, LOW | !moreC);

  // while any actuator has not reached the threshold
  while (!done) {
    // get absolute distance to final pos
    dA = finalPosA - EncA.read();
    dB = finalPosB - EncB.read();
    dC = finalPosC - EncC.read();
    doneA = check_done(dA);
    doneB = check_done(dB);
    doneC = check_done(dC);
    curTime = millis();
    timedOut = timeout(prevTime, curTime);
    done = check_all_done(doneA, doneB, doneC, timedOut);

    if (doneA) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
    if (doneB) {
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    if (doneC) {
      digitalWrite(in5, LOW);
      digitalWrite(in6, LOW);
    }
  }
  turn_off();
  // Short delay to let the encoder come to rest
  delay(100);
}

/*
 * Moves all 3 actuators to the same determined final positions.
 * 
 * finalPos : encoder value for all 
 */
void move_effector_to(long finalPos) {
  move_effector_to(finalPos, finalPos, finalPos);
}

/*
 * Functions: move_A, move_B, move_C
 * 
 * move their corresponding actuators
 */
void move_A(long posA) {
  long posB = EncB.read();
  long posC = EncC.read();
  move_effector_to(posA, posB, posC);
}

void move_B(long posB) {
  long posA = EncA.read();
  long posC = EncC.read();
  move_effector_to(posA, posB, posC);
}

void move_C(long posC) {
  long posA = EncA.read();
  long posB = EncB.read();
  move_effector_to(posA, posB, posC);
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
  long posA = EncA.read();
  move_effector_to(posA, pos, pos);
}

void move_to_B(long pos) {
  long posB = EncB.read();
  move_effector_to(pos, posB, pos);
}

void move_to_C(long pos) {
  long posC = EncC.read();
  move_effector_to(pos, pos, posC);
}

/*
 * Moves the effector in a pseudo hexagonal shape
 */
void move_hex(long pos) {
  move_to_A(pos);
  move_B(0);
  move_A(pos);
  move_C(0);
  move_B(pos);
  move_A(0);
  move_C(pos);
  move_to_A(0);
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
 * calibrate value of encoder to be 0 at bottom
 */
void calib_enc() {
  // Overwrite any value in encoder
  EncA.write(maxEncVal);
  EncB.write(maxEncVal);
  EncC.write(maxEncVal);
  // Move to 0 to guarantee that motors are at the bottom
  move_effector_to(0);
  reset_enc();
}

/*
 * loads current encoder values into pos
 */
void get_cur_pos(long pos[]) {
  pos[0] = EncA.read();
  pos[1] = EncB.read();
  pos[2] = EncC.read();
}
