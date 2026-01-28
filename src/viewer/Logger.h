#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <vector>

class wxTextCtrl;

#define FS() Logger::Log("{");\
             Logger::IncIndentLevel();\
             Logger::Log(__FUNCTION__);\

#define FE() Logger::DecIndentLevel();\
             Logger::Log("}");

class Logger
{
public:

  enum LogLevel
  { 
    TRACE, INFO, WARNING, CRITICAL
  };

  static void Log(const std::string& msg, 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, const std::string& v1, 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, long int val , 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, unsigned long long int val , 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, int v1, 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, int v1, int v2, 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, int v1, int v2, int v3, 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, int v1, int v2, int v3, int v4,
				  LogLevel level = TRACE);
  static void Log(const std::string& msg, float v1, 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, float v1, float v2, 
                  LogLevel level = TRACE);
  static void Log(const std::string& msg, float v1, float v2, float v3, 
                  LogLevel level = TRACE);

  static void IncIndentLevel();
  static void DecIndentLevel();
  
  static void SetLogTarget(wxTextCtrl* target);

  static void SetLevel(LogLevel level)
  {
    m_level = level;
  }

protected:
  static LogLevel m_level;
  static std::string  m_indent;
  static wxTextCtrl* m_logOut;
  Logger();
};


#endif // LOGGER_H