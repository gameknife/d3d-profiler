#ifndef xAPICallMonitor_h__
#define xAPICallMonitor_h__

#include "xd3d9.h"

//#define CHECK_RETCODE

struct xCostElement
{
	uint32 tickPerFrame;
	uint32 countPerFrame;
	bool mute;

	xCostElement()
	{
		tickPerFrame = 0;
		countPerFrame = 0;
		mute = false;
	}
};

typedef stdext::hash_map< std::string, bool > xFuncMap;
typedef stdext::hash_map< std::string, xCostElement > xCostMap;

struct xFuncTicker
{
	xFuncTicker( xCostElement* resultHolder );
	~xFuncTicker();
	xCostElement* m_resultHolder;
	uint32 m_startTick;
};

struct xAPICallMonitor
{
	static void CheckCall( HRESULT returnCode, const char* functionName );
	static void MuteCall( const char* functionName, bool mute );
	static void MuteAll(bool mute);
	static bool ShouldMute( bool mute );
	static void Update();
	static xCostElement* GetCostMapHolder( const char* functionName );

	static xFuncMap s_funcMap;
	static xCostMap s_costMap;
	static bool s_muteAll;
	static bool s_tmpUnMuteAll;
	static bool s_funcTicking;
};

// #ifdef CHECK_RETCODE
// #define CHECKCALL( x, y ) xAPICallMonitor::CheckCall( x, y );
// #else
 #define CHECKCALL( x, y ) 
// #endif

#define ENTERCALL( x ) \
	xCostElement* element = xAPICallMonitor::GetCostMapHolder(x);\
	xFuncTicker xxxx_ticker_xxxx(element);\
	if( xAPICallMonitor::ShouldMute(element->mute) ) return D3D_OK;\

#define ENTERCALL_TICK( x ) \
	xFuncTicker xxxx_ticker_xxxx(xAPICallMonitor::GetCostMapHolder(x));

#define FUNC_ENTER ENTERCALL( __FUNCTION__ )
#define FUNC_ENTER_TICK ENTERCALL_TICK( __FUNCTION__ )

#endif // xAPICallMonitor_h__