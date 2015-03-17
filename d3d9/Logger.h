/**
  @file GtLogger.h
  
  @author Kaiming

  更改日志 history
  ver:1.0
   
 */

#ifndef SrLogger_h__
#define SrLogger_h__

#include "xd3d9.h"

struct ILogger
{
	virtual ~ILogger(void) {}

	virtual void Log(const char* line) =0;
	virtual void LogE(const char* line) =0;
	virtual void LogV(const char* format, va_list args) =0;
};

class xLogger : public ILogger
{
public:
	xLogger(void);
	~xLogger(void);

	void Log(const char* line);
	void LogE(const char* line);
	void LogV(const char* format, va_list args);

private:
	void FlushToFile();
	char* m_data;
	uint32 m_size;

	bool Terminated;
	HANDLE hDebugViewThread;
	uint32 m_nThreadId;
};

#endif

