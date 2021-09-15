#include "motors.h"

/* positions of actuators detected from encoders */
long posA = -999, posB = -999, posC = -999;

void setup() {
  // put your setup code here, to run once:
  setup_motors();

  Serial.begin(9600);
  reset_enc();
}

void loop() {
  print_diff_pos(&posA, &posB, &posC);
  if (Serial.available()) {
    reset_enc();
    char dir = Serial.read();
    long t = Serial.parseInt();
    switch (dir) {
    case 'm':
      move_effector(t);
      break;
    case 'a':
      move_A(t);
      break;
    case 'b':
      move_B(t);
      break;
    case 'c':
      move_C(t);
      break;
    case 't':
      test_move(100);
      break;
    }
  }
}
