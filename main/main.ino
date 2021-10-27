#include "movetest.h"
#include "ui.h"

/* positions of actuators detected from encoders */
long pos[3] = {-999, -999, -999};
long newPos[3];

void setup() {
  setup_motors();

  Serial.begin(9600);
  calib_enc();
}

void loop() {
  get_cur_pos(newPos);
  // Print positions if they ever change
  print_diff_pos(pos, newPos);

  // Check whether Serial is available
  if (!Serial.available())
    return;

  // Goes here if Serial is available
  // Parse character and long integer to use as commands
  char dir = Serial.read();
  long i = Serial.parseInt();
  // Parse long value
  long t = percent_to_pos(i);
  print_parsed_int(i, t);
  
  switch (dir) {
  case 'm':
    move_effector_to(t);
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
    test_full(t);
    break;
  case 'r':
    calib_enc();
    break;
  default:
    print_help();
    break;
  }
  Serial.println("Done!");
}
