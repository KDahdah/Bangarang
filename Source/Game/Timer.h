#include <ctime>
#include <time.h>
#define INITIAL_TIME 2

class TimerC
{
public:
	TimerC(float_t time);
	~TimerC(){};
	void StopTimer();
	void StartTimer();
	void ResetTimer();
	void SetTimeToComplete(float_t time);
	void RunTimer();
	bool8_t isFinished();
	float_t getTime();
private:
	clock_t mStartTime;
	clock_t mEndTime;
	clock_t mTimeToComplete;
	clock_t mCurrentTime;
	bool8_t mActive;
	bool8_t mComplete;
};