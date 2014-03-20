#include "GameTimer.h"


GameTimer::GameTimer( ) : secondsPerCount(0.0), deltaTime(-1.0), baseTime(0), pausedTime(0), prevTime(0), currTime(0), stopped(false)
{
	__int64 _countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&_countsPerSec);
	secondsPerCount = 1.0 / (double)_countsPerSec;
}


GameTimer::~GameTimer( )
{
}


// returns the total time elapsed since reset() was called
// NOT counting any time when the clock is stopped
float GameTimer::GetGameTime()const
{
	// if we are stopped, do not count the time that has passed since we stopped
	//
	// ----*---------------*------------------------------*------> time
	//  baseTime       stopTime                      currTime

	if(stopped)
	{
		return (float)((stopTime - baseTime) * secondsPerCount);
	}

	// the distance mCurrTime - mBaseTime includes paused time, which we do not want to count
	// to correct this, we can subtract the paused time from mCurrTime:  
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------*------> time
	//  baseTime       stopTime        startTime     currTime
	
	else
	{
		return (float)(((currTime-pausedTime)-baseTime) * secondsPerCount);
	}
}

float GameTimer::GetDeltaTime()const
{
	return (float)deltaTime;
}

float GameTimer::GetFPS()
{
	return fps;
}

void GameTimer::Reset()
{
	__int64 _currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&_currTime);

	baseTime = _currTime;
	prevTime = _currTime;
	stopTime = 0;
	stopped  = false;
}

void GameTimer::Start()
{
	__int64 _startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&_startTime);


	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  baseTime       stopTime        startTime     

	if(stopped)
	{
		pausedTime += (_startTime - stopTime);	

		prevTime = _startTime;
		stopTime = 0;
		stopped  = false;
	}
}

void GameTimer::Stop()
{
	if(!stopped)
	{
		__int64 _currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&_currTime);

		stopTime = _currTime;
		stopped  = true;
	}
}

void GameTimer::Tick()
{
	if(stopped)
	{
		deltaTime = 0.0;
		return;
	}

	__int64 _currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&_currTime);
	currTime = _currTime;

	// time difference between this frame and the previous frame
	deltaTime = (currTime - prevTime)*secondsPerCount;

	// prepare for next frame
	prevTime = currTime;

	// ensure delta time is not negative
	if(deltaTime < 0.0)
	{
		deltaTime = 0.0;
	}
}

// ADDITIONAL FUNCTIONS


void GameTimer::CalculateFPS( )
{
	// compute the average frames per second and average time to render one frame
	static int frameCount = 0;
	static float timeBase = 0.0f;

	frameCount++;

	// compute averages over one second
	if( ( GetGameTime( ) - timeBase ) >= 1.0f )
	{
		fps = ( float )frameCount;

		// reset for next average
		frameCount = 0;
		timeBase += 1.0f;
	}
}