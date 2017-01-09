#include "FixtureUserData.h"

FixtureUserData::FixtureUserData(fixtureUserDataType type) : objectValue(type) {
}

fixtureUserDataType FixtureUserData::getType() {
	return objectValue;
}
FixtureUserData::~FixtureUserData() {
}