// ----------------------------------------------------
// Name: functions.cpp
// Description: some small functions needed somewhere.  general functions
// Introduced: chgloor Thursday, August 28, 2003 15:36:48
// ----------------------------------------------------
//#include <stdio.h>                                          // sscanf

// ----------------------------------------------------
// Name: time2sec 
// Description: parses time in format "09:12.01" into seconds since midnight of first day. 
//              also possible "09:12:01" (note the : instead of the .),
//              or "09:12", which means "09:12.00"
//              or "69121", which means "09:12.01" or seconds since midnight
// Introduced: chgloor Thursday, August 28, 2003 15:37:16
// Return value: seconds since midnight of first day
// ----------------------------------------------------
/*
long time2sec (const char *time) {
  long seconds = 0;
  unsigned hh = 0;
  unsigned mm = 0;
  unsigned ss = 0;
  if (3 != sscanf((char *)time, "%u:%u.%u", &hh, &mm, &ss)) {
    if (3 != sscanf((char *)time, "%u:%u.%u", &hh, &mm, &ss)) {
      hh = 0; mm = 0; ss = 0;
      if (2 != sscanf((char *)time, "%u:%u", &hh, &mm)) {
	hh = 0; mm = 0; ss = 0;
	if (1 != sscanf((char *)time, "%u", &ss))  return -1; // error = invalid time string      
      }
    }
  }
  seconds = hh*3600 + mm*60 + ss;
  return seconds;
}
*/
