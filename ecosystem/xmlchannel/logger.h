
#ifndef _logger_h_
#define _logger_h_

#include <string>

class Logger {
 public:
  Logger();
  ~Logger();
  void add(std::string message);
  void operator<<(std::ostream& _o);
};

#endif
