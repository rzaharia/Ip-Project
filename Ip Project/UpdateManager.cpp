#include "UpdateManager.h"
#include <iostream>
using namespace std;
UpdateManager::UpdateManager()
{
}


UpdateManager::~UpdateManager()
{
}

void UpdateManager::TimeManagement(float elapsedTime)
{
	currentTime += elapsedTime;
	if (currentTime > 0.075f)
	{
		currentTime -= 0.075f;
		tick++;
		if (tick == 1001)
			tick = 1;
		UpdateAll(tick);
	}
}

void UpdateManager::UpdateAll(short int tick)//Add update functions here
{ //1 tick ~ 0.1 s
	if (tick % 2 == 0) //0.2 s
	{

	}
}
