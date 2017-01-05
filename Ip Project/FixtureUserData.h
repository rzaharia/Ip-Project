#pragma once
#include "fixtureType.h"

class FixtureUserData {
	fixtureUserDataType objectValue;
protected:
	FixtureUserData(fixtureUserDataType type) : objectValue(type) {};
public:
	virtual fixtureUserDataType getType();
	virtual ~FixtureUserData();
};