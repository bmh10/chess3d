#ifndef _LOGGER_H
#define _LOGGER_H

#include "headers.h"

class Logger
{
  private:
    static std::ofstream outfile;

    static char* GetTime();
    static void Output(string s, string type);

  public:
    static void Init();
    static void Dispose();
    static void Info(string s);
    static void Warn(string s);
    static void Error(string s);

};

#endif
