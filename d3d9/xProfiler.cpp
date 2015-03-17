/**
  @file SrProfiler.cpp
  
  @author Kaiming

  更改日志 history
  ver:1.0
   
 */
#include "xProfiler.h"



xProfiler::xProfiler()
{
	m_profileElements.assign(ePe_Count, xProfilerElement());
	m_profileElements[ePe_ZError].dontClear = true;
}

xProfiler::~xProfiler()
{
}


// void xProfiler::setBegin( EProfilerElement element )
// {
// 	m_profileElements[element].prevTime = gEnv->timer->getRealTime();
// }
// 
// void xProfiler::setEnd( EProfilerElement element )
// {
// 	xProfilerElement& elementInst = m_profileElements[element];
// 	float now = gEnv->timer->getRealTime();
// 	elementInst.elapsedTime = now - elementInst.prevTime;
// }


void xProfiler::IncreaseTime( EProfilerElement element, float time )
{
	m_profileElements[element].elapsedTime += time;
}


void xProfiler::setIncrement( EProfilerElement element, int count /*= 1 */ )
{
	m_profileElements[element].count += count;
}

float xProfiler::getTime( EProfilerElement element )
{
	return m_profileElements[element].elapsedTime;
}

float xProfiler::getAverageTime( EProfilerElement element )
{
	return m_profileElements[element].avgElapsedTime;
}

int xProfiler::getCount( EProfilerElement element )
{
	return m_profileElements[element].count;
}

void xProfiler::Update()
{
	// profile resources


	for (int i = 0; i < ePe_Count; i++)
	{
		m_profileElements[i].Clear();
	}
}
