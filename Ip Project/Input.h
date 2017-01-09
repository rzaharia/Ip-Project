#pragma once
#include "Car.h"

class Input{
public:
	int controlState;
	b2Body* groundBody;
	Car* car;
	b2Vec2 Gravity;
	b2World *World;

	Input();
	~Input();
	void Input::Initialize(); 
	void Input::BeginContact(b2Contact* contact);
	void Input::OutOfContact(b2Contact* contact);
	void Input::tireOrGround(b2Fixture* tireFixture, b2Fixture* groundAreaFixture, bool began);
	void Input::handleContact(b2Contact* contact, bool began);
	void Input::KeyboardUp(unsigned char key);
	void Input::Keyboard(unsigned char key);

};