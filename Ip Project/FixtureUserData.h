#pragma once
#include "fixtureType.h"

class FixtureUserData {
	fixtureUserDataType objectValue;
protected:
	FixtureUserData(fixtureUserDataType type);
public:
	virtual fixtureUserDataType getType();
	virtual ~FixtureUserData();
};