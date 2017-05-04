#include "baseTypes.h"
#include "Timer.h"
#include <stdio.h>

TimerC::TimerC(float_t time)
{
	mTimeToComplete = (clock_t)(time*CLOCKS_PER_SEC);
	mActive = false;
	mComplete = false;
}

void TimerC::ResetTimer()
{
	StartTimer();
}

void TimerC::SetTimeToComplete(float_t time)
{
	mTimeToComplete = (clock_t)time;
}

void TimerC::StartTimer()
{
	mActive = true;
	mStartTime = clock();
	//printf("timer has started at time %d\n", time(0));
}

void TimerC::RunTimer()
{
	if(mActive)
	{
		//printf("TIMER!\n");
		mCurrentTime = clock() - mStartTime;
		//printf("%d",mCurrentTime);
		if(mCurrentTime >= mTimeToComplete)
		{
			//printf("TIMER FINISHED!\n");
			mComplete = true;
			StopTimer();
		}
	}
}

float_t TimerC::getTime()
{
	return (float_t)mCurrentTime;
}

void TimerC::StopTimer()
{
	mActive = false;
}

bool8_t TimerC::isFinished()
{
	bool8_t countdownTrigger = false;
	if(mComplete)
	{
		//printf("sudo boom\n");
		countdownTrigger = true;
		mComplete = false;
	}
	return countdownTrigger;
}