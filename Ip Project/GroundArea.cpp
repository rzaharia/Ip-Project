#include "FixtureUserData.h"

	class GroundArea : public FixtureUserData {
	public:
		float frictionModifier;
		bool outOfCourse;

		GroundArea(float friction, bool course) : FixtureUserData(GROUND_AREA) {
			frictionModifier = friction;
			outOfCourse = course;
		}
	};