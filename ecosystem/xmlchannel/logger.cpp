/// The Logger class implements a simple way of logging output.
/// For now, it only sends it to the console, but it can easily be rewritten that it uses the system log instead.

#include <syslog.h>

#include <iostream>
#include <string>
#include <iomanip>

#include <time.h>
#include <sstream>

#include "logger.h"

using namespace std;

/// Constructor
/// \author  chgloor
/// \date    Friday, July 13, 2007 12:39:03
Logger::Logger() {
  //  openlog("controlchannel", LOG_PID, LOG_USER);
}

/// Destructor
/// \author  chgloor
/// \date    Friday, July 13, 2007 12:39:03
Logger::~Logger() {
  //  closelog();
}

/// Prints the string with a date in front.
/// \author  chgloor
/// \date    Wednesday, Friday, July 13, 2007 12:39:03
/// \param   message The message that should be put into the log
void Logger::add(string message) {
  time_t rawtime;
  time ( &rawtime );  
  struct tm *t;
  t = localtime(&rawtime);

  ostringstream os; 

  os << "[" << t->tm_year+1900 << "-" << setw(2) << setfill('0') << t->tm_mon+1 << "-" << setw(2) << setfill('0') << t->tm_mday << " "  ;
  os << setw(2) << setfill('0') << t->tm_hour << ":" << setw(2) << setfill('0') << t->tm_min << "." << setw(2) << setfill('0') << t->tm_sec << "] ";
  os << message << ends;
  cout << os.str() << endl;
  
  //syslog(LOG_INFO, os.str().c_str());
}

