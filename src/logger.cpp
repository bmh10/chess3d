#include "logger.h"

std::ofstream Logger::outfile;

void Logger::Init()
{
  outfile.open("../logs/log.txt", std::ios_base::app);
  Info("--------------- LOGGER STARTED ---------------");
}

void Logger::Dispose()
{
  outfile.close();
}
 
void Logger::Info(string s)
{
  Logger::Output(s, "INFO");
}

void Logger::Warn(string s)
{
  Logger::Output(s, "WARN");
}

void Logger::Error(string s)
{
  Logger::Output(s, "ERROR");
}

// ## Private Methods ## //

char* Logger::GetTime()
{
  char* timeBuff = new char[30];
  time_t tTime = time(NULL);
  strftime(timeBuff, 30, "%F %T", localtime(&tTime));
  return timeBuff;
}

void Logger::Output(string s, string type)
{
  if (DEBUG)
  {
    char str[500];
    sprintf(str, "(%s)(%s) %s", GetTime(), type.c_str(), s.c_str());
    outfile << str << endl;
  }
}

