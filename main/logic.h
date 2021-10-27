#ifndef LOGIC_H
#define LOGIC_H

// Timeout Value for movement
const int timeoutVal = 5000;
// Maximum possible encoder value
const long maxEncVal = 50000;
// Threshold for how close encoder value should be to true value
const int epsilon = 500;

/* to check if distance is covered */
bool check_done(long);
bool check_all_done(bool, bool, bool, bool);
/* check validity of position */
long check_pos(long);
/* timeout function */
bool timeout(unsigned long, unsigned long);
/* convert percent to pos */
long percent_to_pos(long);

#endif
