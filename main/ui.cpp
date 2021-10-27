#include "ui.h"

/*
 * prints the encoder values if any position was updated
 * 
 * pos: array of old positions
 * newPos: array of new positions
 */
void print_diff_pos(long pos[], long newPos[]) {
  bool changed = false;

  for (int i = 0; i < 3; ++i) {
    changed |= pos[i] == newPos[i];
    newPos[i] = pos[i];
  }

  if (!changed)
    return;

  Serial.print("A:");
  Serial.println(newPos[0]);
  Serial.print("B:");
  Serial.println(newPos[1]);
  Serial.print("C:");
  Serial.println(newPos[2]);
}

void print_help() {
  Serial.println("Unknown command");
  Serial.println("Here are some commands you can use");
  Serial.println("h       : Pulls up this help text");
  Serial.println("t       : Tests movement, and identifies actuators A, B, C");
  Serial.println("r       : Recalibrate actuators");
  Serial.println("m [pos] : Moves all actuators to position [pos]");
  Serial.println("a [pos] : Moves all actuators A to position [pos]");
  Serial.println("b [pos] : Moves all actuators B to position [pos]");
  Serial.println("c [pos] : Moves all actuators C to position [pos]");
  Serial.println();
  Serial.print("Valid long values for [pos] are 0 <= [pos] <= 50000");
  Serial.println("If 0 <= [pos] <= 100, [pos] will be treated as a percentage");
}

/*
 * prints the parsed integer value
 * 
 * i : old value
 * t : new value
 */
void print_parsed_int(long i, long t) {
  if (i == t) {
    Serial.print("Position parsed as ");
    Serial.println(t);
    return;
  }
  Serial.print("Original value ");
  Serial.print(i);
  Serial.print(" parsed as ");
  Serial.println(t);
}
