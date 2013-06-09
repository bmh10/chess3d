#ifndef _LOGGER_H
#define _LOGGER_H

#include "headers.h"

class Logger
{
  private:

  public:
    static void Info(string s);
    static void Warn(string s);
    static void Error(string s);

};

#endif
