#ifndef circ_log_h
#define circ_log_h

#include <TimeLib.h> //https://github.com/PaulStoffregen/Time
#include <stdlib.h>

template <int elementCnt> class circular_log
{
private:
  char m_log[elementCnt];
  
  bool removeLastFromLog()
  {
    char* nextLine = strstr(m_log+1, "<BR>");
    if(nextLine == NULL)
    {
      return false;
    }

    int newLineLen = strlen(nextLine);
    memmove(m_log, nextLine, newLineLen);
    m_log[newLineLen] = '\0';

    return true;
  }
  
public:
  circular_log()
  {
    memset(m_log, 0, sizeof(m_log));
  }
  
  const char* c_str() const { return m_log; }
  int freeSpace() const { return elementCnt - strlen(m_log) - 1; }

  void LogXml(const char* msg)
  {
    char szNew[256] = "";
    snprintf(szNew, sizeof(szNew)-1, "<BR>%02d - %02d:%02d | ", day(), hour(), minute());

    int ix = strlen(szNew);
    while(*msg != '\0' && ix < 250)
    {
      if(*msg == '<')
      {
        szNew[ix++] = '&';
        szNew[ix++] = 'l';
        szNew[ix++] = 't';
        szNew[ix++] = ';';
      }
      else if(*msg == '>')
      {
        szNew[ix++] = '&';
        szNew[ix++] = 'g';
        szNew[ix++] = 't';
        szNew[ix++] = ';';
      }
      else
      {
        szNew[ix++] = *msg;
      }
      
      msg++;
    }
    
    const int newLen = strlen(szNew);
    while(freeSpace() < newLen)
    {
      if(removeLastFromLog() == false)
      {
        return;
      }
    }

    strcat(m_log, szNew);
  }
  
  void Log(const char* msg)
  {
    char szNew[256] = "";
    snprintf(szNew, sizeof(szNew)-1, "<BR>%02d - %02d:%02d | %s", day(), hour(), minute(), msg);

    const int newLen = strlen(szNew);
    while(freeSpace() < newLen)
    {
      if(removeLastFromLog() == false)
      {
        return;
      }
    }

    strcat(m_log, szNew);
  }
};

#endif //circular_log_h