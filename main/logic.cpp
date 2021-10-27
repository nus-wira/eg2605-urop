#include "logic.h"

/*
 * Checks value is within threshold
 * -epsilon < dist < epsilon
 * 
 * dist : distance value to check
 * 
 * return : whether check passes
 */
bool check_done(long dist) {
  if (dist < 0)
    dist = -dist;
  return dist < epsilon;
}

/*
 * Checks whether all are done
 * 
 * a : whether motor A is done
 * b : whether motor B is done
 * c : whether motor C is done
 * t : whether timeout has been reached
 * 
 * return : whether check passes
 */
bool check_all_done(bool a, bool b, bool c, bool t) {
  return (a && b && c) || t;
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
 * timeout function if > timeoutVal seconds passed
 */
bool timeout(unsigned long prevTime, unsigned long curTime) {
  return curTime - prevTime > timeoutVal;
}

/*
 * convert percentage value to position value
 *
 * percent : value in percentage
 * 
 * return : position value
 */
long percent_to_pos(long percent) {
  long pos;
  
  // (-inf, 0]
  if (percent <= 0)
    pos = 0;
    
  // (maxEncVal, inf)
  else if (percent > maxEncVal)
    pos = maxEncVal;
    
  // (100, maxEncVal]
  else if (percent > 100)
    pos = percent;
    
  // (0, 100]
  else
    // Convert from percentage
    pos = percent * maxEncVal / 100;
  
  return pos;
}