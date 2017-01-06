#include "FixtureUserData.h"
#include "GroundArea.h"

GroundArea::GroundArea(float friction, bool course) : FixtureUserData(GROUND_AREA) {
	frictionModifier = friction;
	outOfCourse = course;
}