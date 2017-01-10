#include <Box2d.h>
#include "Car.h"
#include "Input.h"
#include "DestructionListener.h"

Input::Input() {
	Initialize();
}

Input::~Input() {
	car->~Car();
	World->ClearForces();
}

void Input::Initialize() {
	Gravity.Set(0.f, 0.f);
	World = new b2World(Gravity);
	DestructionListener destructionListener;
	World->SetDestructionListener(&destructionListener);
	car = new Car(World);
}

void Input::Keyboard(unsigned char key) {
	switch (key) {
	case 'a':
		controlState |= LEFT;
		break;
	case 'd':
		controlState |= RIGHT;
		break;
	case 'w':
		controlState |= UP;
		break;
	case 's':
		controlState |= DOWN;
		break;
	default:
		break;
	}
	car->Update(controlState);  //Added update
}

void Input::KeyboardUp(unsigned char key) {
	switch (key) {
	case 'a':
		controlState &= ~LEFT; 
		break;
	case 'd':
		controlState &= ~RIGHT;
		break;
	case 'w':
		controlState &= ~UP; 
		break;
	case 's':
		controlState &= ~DOWN;
		break;
	default:
		break;
	}
	car->Update(controlState);  //Added update
}

void Input::handleContact(b2Contact* contact, bool began) {

	b2Fixture* FixtureA = contact->GetFixtureA();
	b2Fixture* FixtureB = contact->GetFixtureB();

	FixtureUserData* FixtureUserDataA = (FixtureUserData*)FixtureA->GetUserData();
	FixtureUserData* FixtureUserDataB = (FixtureUserData*)FixtureB->GetUserData();

	if (!FixtureUserDataA || !FixtureUserDataB)
		return;

	if (FixtureUserDataA->getType() == TIRE || FixtureUserDataB->getType() == GROUND_AREA)
		tireOrGround(FixtureA, FixtureB, began);
	else if (FixtureUserDataA->getType() == GROUND_AREA || FixtureUserDataB->getType() == TIRE)
		tireOrGround(FixtureB, FixtureA, began);
}

void Input::BeginContact(b2Contact* contact) {
	handleContact(contact, true);
}

void Input::OutOfContact(b2Contact* contact) {
	handleContact(contact, false);
}

void Input::tireOrGround(b2Fixture* tireFixture, b2Fixture* groundAreaFixture, bool began) {

	Tire* tire = (Tire*)tireFixture->GetBody()->GetUserData();
	GroundArea* groundAreaFixtureUserData = (GroundArea*)groundAreaFixture->GetUserData();

	if (began)
		tire->addGroundArea(groundAreaFixtureUserData);
	else
		tire->removeGroundArea(groundAreaFixtureUserData);
}