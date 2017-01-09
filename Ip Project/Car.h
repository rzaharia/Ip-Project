#pragma once
#include <Box2d.h>
#include <vector>
#include "Tire.h"

// Maximum speed of the car ( the reverse maximum is MAX_SPEED/6.25 )
#define MAX_SPEED 250.0f

// The transmission to all the cars will be on front. ( front wheel-drive )
#define BACK_TIRE_FORCE_TRACTION 600.0f
#define FRONT_TIRE_FORCE 1000.0f

// Lateral force is needed for the car to look like a real car and not like a car on rails. 
// This information won't be available to the students.
#define BACK_TIRE_FORCE_LATERAL 5.5f
#define FRONT_TIRE_FORCE_LATERAL 4.5f

// Steering lock angle and movement per sec.
#define STEER_MOVEMENT_PER_SECOND 0.0174533f
#define STEER_LOCK_ANGLE 32.5f

class Car {
	b2Body* chassis;
	std::vector<Tire*> tires;
	b2RevoluteJoint *frontLeftJoint, *frontRightJoint;
#pragma region Tire specifications

	float maxAccelerationSpeed = MAX_SPEED;
	float maxAccelerationReverseSpeed = -1.0f * MAX_SPEED / 6.25f;
	float backTireMaxLateralForce = BACK_TIRE_FORCE_LATERAL;
	float backTireMaxDriveForce = BACK_TIRE_FORCE_TRACTION;
	float frontTireMaxLateralForce = FRONT_TIRE_FORCE;
	float frontTireMaxDriveForce = BACK_TIRE_FORCE_TRACTION;

#pragma endregion
public:
	void CreateTireAndFixItToCarBody(b2World* world, b2RevoluteJointDef bodyJoint, b2Vec2 anchorPosition, bool backTireOrNo);
	Car(b2World* world);
	~Car();
	void update(int state);
};