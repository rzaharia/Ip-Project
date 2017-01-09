#include "Box2d.h"
#include "FixtureUserData.h"

class DestructionListener : public b2DestructionListener {
	void SayGoodbye(b2Fixture* fixture);
	void SayGoodbye(b2Joint* joint);
};