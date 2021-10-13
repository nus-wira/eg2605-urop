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
    // Small value is interpreted as percentage
    if (t >= -100 && t <= 100) {
      t = percent_to_pos(t);
    }
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
    case 'h':
      move_hex(t);
      break;
    case 't':
      test_full(t);
      break;
    }
  }
}
