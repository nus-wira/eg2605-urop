#include "movetest.h"

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