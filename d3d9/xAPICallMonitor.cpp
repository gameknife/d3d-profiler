#include "xAPICallMonitor.h"
#include <stdio.h>
#include "timer.h"
#include "Logger.h"

xFuncMap xAPICallMonitor::s_funcMap;
xCostMap xAPICallMonitor::s_costMap;
bool xAPICallMonitor::s_muteAll = false;
bool xAPICallMonitor::s_tmpUnMuteAll = false;
bool xAPICallMonitor::s_funcTicking = false;

void xAPICallMonitor::CheckCall( HRESULT returnCode, const char* functionName )
{
	if ( FAILED(returnCode) )
	{
		char buffer[1024];
		sprintf(buffer, "xD3D9: (CALL FAILED) : %s\n", functionName);
		gEnv->logger->LogE(buffer);
	}
}

void xAPICallMonitor::MuteCall( const char* functionName, bool mute )
{
	s_costMap[functionName].mute = mute;
}

bool xAPICallMonitor::ShouldMute( bool mute )
{
	if (s_tmpUnMuteAll)
	{
		return false;
	}

	if (s_muteAll)
	{
		return true;
	}

	return mute;
}

void xAPICallMonitor::MuteAll( bool mute )
{
	s_muteAll = mute;
}

void xAPICallMonitor::Update()
{
	if ( s_funcTicking )
	{
		xCostMap::iterator it = s_costMap.begin();
		for (; it != s_costMap.end(); ++it)
		{
			it->second.tickPerFrame = 0;
			it->second.countPerFrame = 0;
		}
	}
}

xCostElement* xAPICallMonitor::GetCostMapHolder( const char* functionName )
{
	return &( s_costMap[functionName] );
}

xFuncTicker::xFuncTicker( xCostElement* resultHolder ):m_resultHolder(resultHolder)
{
	m_startTick = g_timer->getRealTick();
}

xFuncTicker::~xFuncTicker()
{
	m_resultHolder->tickPerFrame += (g_timer->getRealTick() - m_startTick);
	m_resultHolder->countPerFrame++;
}
