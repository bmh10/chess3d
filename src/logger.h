#ifndef _LOGGER_H
#define _LOGGER_H

class Logger
{
  private:

  public:
    static void WriteInfo(string s);
    static void WriteWarn(string s);
    static void WriteError(string s);

};

#endif