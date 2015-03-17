#include "Logger.h"
#include "SharedMem.h"
#include "thread.h"

const int LOG_FILE_SZIE = 1024 * 1;


struct dbwin_buffer {
	DWORD   dwProcessId;
	char    data[4096-sizeof(DWORD)];
};

CRITICAL_SECTION g_cs;

uint32 __stdcall DebugViewThreadProc(void* pv)
{
    /********************************************************************************************
     * 1. Create the shared memory segment and the two events. If we can't, exit.
     * 2. Set the DBWIN_BUFFER_READY event so the applications know that the buffer is available.
     * 3. Wait for the DBWIN_DATA_READY event to be signaled.
     * 4. Extract the process ID NUL-terminated string from the memory buffer.
     * 5. Go to step #2
     ********************************************************************************************/
        TSharedMem sm("DBWIN_BUFFER", sizeof(struct dbwin_buffer));

        char szFileName[MAX_PATH];
        HANDLE hBufReadyEvent = CreateEvent(
                                  NULL,         // no security attributes
                                  FALSE,         // auto-reset event
                                  FALSE,         // initial state is nonsignaled
                                  "DBWIN_BUFFER_READY"  // object name
                                  );
        if (hBufReadyEvent == NULL)
        {
            MessageBox(GetActiveWindow(),
                       "Cannot create event of DBWIN_BUFFER_READY",
                       NULL,
                       MB_OK);
            return 0;
        }
        HANDLE hDataReadyEvent = CreateEvent(
                                      NULL,         // no security attributes
                                      FALSE,         // auto-reset event
                                      FALSE,         // initial state is nonsignaled
                                      "DBWIN_DATA_READY"  // object name
                                      );
        if (hBufReadyEvent == NULL)
        {
            MessageBox(GetActiveWindow(),
                       "Cannot create event of DBWIN_DATA_READY",
                       NULL,
                       MB_OK);
            return 0;
        }
        while(1)
        {
           ::SetEvent(hBufReadyEvent);
           ::WaitForSingleObject(hDataReadyEvent, INFINITE);
           if(0)       //Thread terminated flag
           {
               ::SetEvent(hBufReadyEvent);
               CloseHandle(hBufReadyEvent);
               CloseHandle(hDataReadyEvent);
               return 0;
           }
           dbwin_buffer DebugString = *((struct dbwin_buffer*)(sm.Buffer()));
           //EnterCriticalSection(&g_cs);
  
  //display the result string
  //including PID,Output string, Process Path
//            Item = MainForm->DebugListView->Items->Add();
//            Item->Caption = IntToStr(MainForm->DebugListView->Items->Count);
//            Item->SubItems->Add(IntToStr(DebugString.dwProcessId));
//            Item->SubItems->Add(DebugString.data);
//            Item->SubItems->Add(GetProcessPath(DebugString.dwProcessId, szFileName));
//            ListView_EnsureVisible(MainForm->DebugListView->Handle,MainForm->DebugListView->Items->Count-1,false);

		  if ( strstr( DebugString.data, "Direct3D") )
		  {
			  //gEnv->logger->LogE(DebugString.data);
		  }	  

          //LeaveCriticalSection(&g_cs);
        }

	return 0;
}


xLogger::xLogger(void)
{
	// 1mb
	m_data = new char[LOG_FILE_SZIE];
	m_size = 0;
	Terminated = false;

	AllocConsole();
	freopen("CONOUT$","w+t",stdout);  
	freopen("CONIN$","r+t",stdin);

	//InitializeCriticalSection( &g_cs );
	hDebugViewThread = (HANDLE)::_beginthreadex(0, 0, DebugViewThreadProc, (void*)this, 0, &m_nThreadId);

	//Log( GetCommandLine());

	FlushToFile();

}

xLogger::~xLogger(void)
{
	::TerminateThread(hDebugViewThread, 0);
	//DeleteCriticalSection( &g_cs );

	FlushToFile();

	delete[] m_data;

	fclose(stdout);
	fclose(stdin);
	FreeConsole();
}

void xLogger::Log( const char* line )
{
	uint32 length = strlen(line);
	
	// 缓存装不下了，写入文件
	if (m_size + length + 2 > LOG_FILE_SZIE)
	{
		FlushToFile();
	}

	// 装入缓存
	{
		SYSTEMTIME time;
		GetSystemTime(&time);

		char* buffer = new char[length + 100];

		int infoType = 0;
		static HANDLE consolehwnd;
		consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);

		switch(line[1])
		{
		case '0':
			SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );
			break;
		case '1':
			SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE | FOREGROUND_GREEN );
			break;
		case '2':
			SetConsoleTextAttribute(consolehwnd, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
			break;
		case '3':
			SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED | FOREGROUND_INTENSITY );
			break;
		}

		sprintf(buffer, "[%d/%d/%d %d:%d(+8)] %s \r\n", time.wYear, time.wMonth, time.wDay, (time.wHour + 8) % 24, time.wMinute, line + 2);


		memcpy( m_data + m_size, buffer, strlen(buffer) );
		m_size += strlen(buffer);

		freopen("CONOUT$","w+t",stdout);  
		freopen("CONIN$","r+t",stdin);
		std::cout << buffer;

		delete[] buffer;
	}
	
}

void xLogger::LogE( const char* line )
{
	char buffer[2048];
	sprintf(buffer, "$3%s", line);
	Log( buffer );
}
void xLogger::LogV( const char* format, va_list args )
{
	char buffer[2048];
	vsprintf( buffer, format, args );

	Log( buffer );
}

void xLogger::FlushToFile()
{
	// write to file
	FILE* pFile = NULL;

	std::string path("xd3d_log.txt");
	//getMediaPath( path );

	fopen_s( &pFile, path.c_str(), "ab");

	fwrite( m_data, 1, m_size, pFile );

	fclose(pFile);

	// remove size to 0
	m_size = 0;
}
