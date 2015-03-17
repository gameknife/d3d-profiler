/**
  @file SrProfiler.h
  
  @author Kaiming

  更改日志 history
  ver:1.0
   
 */

#ifndef SrProfiler_h__
#define SrProfiler_h__

#include "xd3d9.h"

#define AVGTIME_COUNT 60

enum EProfilerElement
{
	ePe_FlushTime = 0,
	ePe_ClearTime,
	ePe_VertexShaderTime,
	ePe_RasterizeShaderTime,
	ePe_PixelShaderTime,
	ePe_FrameTime,
	ePe_FlushTextTime,
	ePe_PostProcessTime,

	ePe_DrawCallTime,
	ePe_DrawCallAllocTime,

	ePe_DPCount,
	ePe_DIPCount,

	ePe_DPUCount,
	ePe_DIPUCount,

	ePe_DPTimeTotal,
	ePe_DPTickCount,

	ePe_SetTextureCount,

	ePe_StateChangeCount,
	ePe_StateChangeTime,

	ePe_ProfilerCostTime,

	ePe_TriangleCount,
	ePe_RasterizeCount,
	ePe_PixelCount,
	ePe_VertexCount,
	ePe_ZError,

	// gpu mark

	ePe_Count,
};

// struct IProfiler
// {
// 	virtual ~IProfiler() {}
// 
// 	virtual void Update() =0;
// 
// 	virtual void setBegin( EProfilerElement element ) =0;
// 	virtual void setEnd( EProfilerElement element ) =0;
// 	virtual void IncreaseTime( EProfilerElement element, float time ) =0;
// 	virtual void setIncrement( EProfilerElement element, int count = 1 ) =0;
// 	virtual float getTime( EProfilerElement element ) =0;
// 	virtual float getAverageTime( EProfilerElement element ) =0;
// 	virtual int getCount( EProfilerElement element ) =0;
// 
// // 	virtual void setGPUBegin( EProfilerElement element ) =0;
// // 	virtual void setGPUEnd( EProfilerElement element ) =0;
// };


struct xProfilerElement
{
	xProfilerElement()
	{
		memset(this, 0, sizeof(*this));
		for (int i=0; i < AVGTIME_COUNT; ++i)
		{
			prevElapsedTime[i] = 0.03f;
		}
		dontClear = false;
	}

	// time element
	float prevTime;
	float elapsedTime;
	float avgElapsedTime;
	float avgTimer;

	float prevElapsedTime[AVGTIME_COUNT];
	int nextTimeIdx;
	// count element
	int	count;
	bool dontClear;
	bool gpuIssue;

	void Clear()
	{
		if(!dontClear)
		{
			count = 0;
		}		

		// TODO: average frametime set
		// 每0.25秒一次？
		
		prevElapsedTime[nextTimeIdx] = elapsedTime;
		if (++nextTimeIdx == AVGTIME_COUNT)
		{
			nextTimeIdx = 0;
		}

		// 计算平均时间
		avgElapsedTime = 0;
		for ( int i=0; i < AVGTIME_COUNT; ++i )
		{
			avgElapsedTime += prevElapsedTime[i];
		}
		avgElapsedTime /= ((float)AVGTIME_COUNT);

		if (avgElapsedTime < 0)
		{
			avgElapsedTime = 0;
		}

		elapsedTime = 0;
	}
};


class xProfiler
{
public:
	xProfiler();
	~xProfiler();

	void Update();

	void setBegin( EProfilerElement element );
	void setEnd( EProfilerElement element );
	void IncreaseTime( EProfilerElement element, float time );
	void setIncrement( EProfilerElement element, int count = 1 );
	float getTime( EProfilerElement element );
	float getAverageTime( EProfilerElement element );
	int getCount( EProfilerElement element );

	void setGPUBegin( EProfilerElement element );
	void setGPUEnd( EProfilerElement element );

private:
	std::vector<xProfilerElement> m_profileElements;
};

#endif