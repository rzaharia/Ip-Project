#include "DestructionListener.h"

void DestructionListener::SayGoodbye(b2Fixture* fixture) {
	if (FixtureUserData* data = (FixtureUserData*)fixture->GetUserData())
		delete data;
}

// virtual function ( C++ is nice :@ )
void DestructionListener::SayGoodbye(b2Joint* joint) {}