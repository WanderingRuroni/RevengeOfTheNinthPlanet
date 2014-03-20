#ifndef _GAME_TIMER_H_
#define _GAME_TIMER_H_

#include <windows.h>

using namespace std;


class GameTimer
{
	public:
		GameTimer( );
		~GameTimer( );

		float GetGameTime( )const;  // in seconds
		float GetDeltaTime( )const; // in seconds

		float GetFPS( );

		void Reset( ); // call before message loop.
		void Start( ); // call when unpaused.
		void Stop( );  // call when paused.
		void Tick( );  // call every frame.

		void CalculateFPS( );

	private:
		double secondsPerCount;
		double deltaTime;

		float fps;

		__int64 baseTime;
		__int64 pausedTime;
		__int64 stopTime;
		__int64 prevTime;
		__int64 currTime;

		bool stopped;
};

#endif