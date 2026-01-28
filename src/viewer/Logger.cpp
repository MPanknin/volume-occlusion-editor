#include <wx/generic/textdlgg.h>

#include "Logger.h"

// ===============================================================
Logger::LogLevel Logger::m_level = Logger::TRACE;
std::string     Logger::m_indent = "";
wxTextCtrl*     Logger::m_logOut = 0;

// ===============================================================
void Logger::Log( const std::string& msg , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf(msg.c_str());
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, float val, LogLevel level )
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %.4f", msg.c_str(), val);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%.3f"), val));
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, int val , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %i", msg.c_str(), val);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), val));
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, long int val , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %i", msg.c_str(), val);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), val));
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, unsigned long long int val , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %llu", msg.c_str(), val);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), val));
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, const std::string& val , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %s", msg.c_str(), val.c_str());
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(val);
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, int v1, int v2 , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %i %i", msg.c_str(), v1, v2);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), v1));
  m_logOut->AppendText(" ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), v2));
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, int v1, int v2, int v3 , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %i %i %i", msg.c_str(), v1, v2, v3);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;
  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), v1));
  m_logOut->AppendText(" ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), v2));
  m_logOut->AppendText(" ");
  m_logOut->AppendText(wxString::Format(wxT("%i"), v3));
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, int v1, int v2, int v3, int v4, LogLevel level)
{
	if(level < m_level) return;

	printf(m_indent.c_str());
	printf("%s: %i %i %i %i", msg.c_str(), v1, v2, v3, v4);
	printf("\n");

	if(msg.length() < 2) return;
	if(!m_logOut) return;
	m_logOut->AppendText(msg);
	m_logOut->AppendText(": ");
	m_logOut->AppendText(wxString::Format(wxT("%i"), v1));
	m_logOut->AppendText(" ");
	m_logOut->AppendText(wxString::Format(wxT("%i"), v2));
	m_logOut->AppendText(" ");
	m_logOut->AppendText(wxString::Format(wxT("%i"), v3));
	m_logOut->AppendText(" ");
	m_logOut->AppendText(wxString::Format(wxT("%i"), v4));
	m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::Log( const std::string& msg, float v1, float v2 , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %f %f", msg.c_str(), v1, v2);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;

  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%f"), v1));
  m_logOut->AppendText(" ");
  m_logOut->AppendText(wxString::Format(wxT("%f"), v2));
  m_logOut->AppendText("\n");
}

// ===============================================================
void Logger::Log( const std::string& msg, float v1, float v2, float v3 , LogLevel level)
{
  if(level < m_level) return;

  printf(m_indent.c_str());
  printf("%s: %f %f %f", msg.c_str(), v1, v2, v3);
  printf("\n");

  if(msg.length() < 2) return;
  if(!m_logOut) return;

  m_logOut->AppendText(msg);
  m_logOut->AppendText(": ");
  m_logOut->AppendText(wxString::Format(wxT("%f"), v1));
  m_logOut->AppendText(" ");
  m_logOut->AppendText(wxString::Format(wxT("%f"), v2));
  m_logOut->AppendText(" ");
  m_logOut->AppendText(wxString::Format(wxT("%f"), v3));
  m_logOut->AppendText("\n");
}
// ===============================================================
void Logger::IncIndentLevel()
{
  Logger::m_indent.append("  ");
}
// ===============================================================
void Logger::DecIndentLevel()
{
  m_indent = m_indent.substr(2);
}
// ===============================================================
void Logger::SetLogTarget( wxTextCtrl* target )
{
  m_logOut = target;
}
