#pragma once
class UpdateManager
{
public:
	UpdateManager();
	~UpdateManager();

	void TimeManagement(float elapsedTime);

private:
	float currentTime = 0.f;
	short int tick = 0;

	void UpdateAll(short int tick);
};

