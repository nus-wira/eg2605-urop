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
  unsigned long prevTime = millis();
  finalPosA = check_pos(finalPosA);
  finalPosA = check_pos(finalPosB);
  finalPosA = check_pos(finalPosC);

  long dA = finalPosA - EncA.read();
  long dB = finalPosB - EncB.read();
  long dC = finalPosC - EncC.read();
  bool moreA = dA > 0;
  bool moreB = dB > 0;
  bool moreC = dC > 0;
  bool done = false, doneA = false, doneB = false, doneC = false;

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
    dA = dA > 0 ? dA : -dA;
    dB = dB > 0 ? dB : -dB;
    dC = dC > 0 ? dC : -dC;
    doneA = dA < epsilon;
    doneB = dB < epsilon;
    doneC = dC < epsilon;
    done = (doneA && doneB && doneC) || timeout(prevTime);

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
 * Checks validity of position, and returns a value within range if not
 * 
 * pos : position value to check
 * 
 * return : valid position value
 */
long check_pos(long pos) {
  if (pos > maxEncVal)
    return maxEncVal;
  if (pos < 0)
    return 0;
  return pos;
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
 * movement test for A, B, C, in that order.
 * can be used to determine A, B, C.
 */
void test_move(long pos) {
  move_A(pos);
  move_A(0);
  move_B(pos);
  move_B(0);
  move_C(pos);
  move_C(0);
  turn_off();
}

/*
 * movement test for A,B,C, then
 * movement test for hexagon
 */
void test_full(long pos) {
  Serial.print("pos value: ");
  Serial.println(pos);
  Serial.println("check A,B,C");
  test_move(pos);
  Serial.println("moving to A");
  move_to_A(pos);
  move_to_A(0);
  Serial.println("moving to B");
  move_to_B(pos);
  move_to_B(0);
  Serial.println("moving to C");
  move_to_C(pos);
  move_to_C(0);
  Serial.println("moving hexagonal");
  move_hex(pos);
  turn_off();
}

/*
 * convert percentage value to position value
 *
 * percent : value in percentage
 * 
 * return : position value
 */
long percent_to_pos(int percent) {
  if (percent > 100)
    percent = 100;
  else if (percent < 0)
    percent = 0;
  long pos = percent * maxEncVal / 100;
  return pos;
}

/*
 * timeout function if > 10 seconds passed
 */
bool timeout(unsigned long prevTime) {
  unsigned long curTime = millis();
  return curTime - prevTime > timeoutVal;
}

/*
 * calibrate value of encoder to be 0 at bottom
 */
void calib_enc() {
  unsigned long curTime = millis();
  // Overwrite any value in encoder
  EncA.write(maxEncVal);
  EncB.write(maxEncVal);
  EncC.write(maxEncVal);
  move_effector_to(-maxEncVal);
  reset_enc();
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

void print_pos() {
  long posA = -999, posB = -999, posC = -999;
  print_diff_pos(&posA, &posB, &posC);
}