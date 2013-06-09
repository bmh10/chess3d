#include "logger.h"


// TODO: output logs to file.

void Logger::Info(string s)
{
  if (DEBUG)
  {
    cout << "INFO: " << s << endl;
  }
}

void Logger::Warn(string s)
{
  if (DEBUG)
  {
    cout << "WARN: " << s << endl;
  }
}

void Logger::Error(string s)
{
  if (DEBUG)
  {
    cout << "ERROR: " << s << endl;
  }
}
