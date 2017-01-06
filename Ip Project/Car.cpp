#include "Car.h"

class Car {
	b2Body* chassis;
	std::vector<Tire*> tires;
	b2RevoluteJoint *frontLeftJoint, *frontRightJoint;

private:
#pragma region Tire specifications

	float maxAccelerationSpeed = MAX_SPEED;
	float maxAccelerationReverseSpeed = -1.0f * MAX_SPEED / 6.25f;
	float backTireMaxLateralForce = BACK_TIRE_FORCE_LATERAL;
	float backTireMaxDriveForce = BACK_TIRE_FORCE_TRACTION;
	float frontTireMaxLateralForce = FRONT_TIRE_FORCE;
	float frontTireMaxDriveForce = BACK_TIRE_FORCE_TRACTION;

#pragma endregion

public:

	Car(b2World* world) {

#pragma region Create the car body

		// Create box2d object for a car.
		b2BodyDef bodyCarType;
		bodyCarType.type = b2_dynamicBody;
		chassis = world->CreateBody(&bodyCarType);
		chassis->SetAngularDamping(3);

		// Create a box body for the car.
		b2Vec2 vertices[4];
		vertices[0].Set(3, 0);
		vertices[1].Set(3, 10);
		vertices[2].Set(-3, 10);
		vertices[3].Set(-3, 0);
		b2PolygonShape polygonShape;
		polygonShape.Set(vertices, 4);
		b2Fixture* fixture = chassis->CreateFixture(&polygonShape, 0.1f);

		// Create a joint for the center of the car.
		b2RevoluteJointDef bodyJoint;
		bodyJoint.bodyA = chassis;
		bodyJoint.enableLimit = true;
		bodyJoint.lowerAngle = 0;
		bodyJoint.upperAngle = 0;
		bodyJoint.localAnchorB.SetZero();

#pragma endregion

#pragma region Create the tires and fix them to the car body.

		// Back left
		CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(-3.0f, 0.75f), true);
		// Back right
		CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(3.0f, 0.75f), true);
		// Front left
		CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(-3.0f, 8.5f), false);
		// Front right
		CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(3.0f, 8.5f), false);

#pragma endregion

	}

	~Car() {
		for (int i = 0; i < tires.size(); i++)
			delete tires[i];
	}

	void CreateTireAndFixItToCarBody(b2World* world, b2RevoluteJointDef bodyJoint, b2Vec2 anchorPosition, bool backTireOrNo) {
		Tire* tire = new Tire(world);
		if (backTireOrNo) {
			tire->setCharacteristics(maxAccelerationSpeed, maxAccelerationReverseSpeed, backTireMaxDriveForce, backTireMaxLateralForce);
			bodyJoint.localAnchorA = anchorPosition;
			world->CreateJoint(&bodyJoint);
		}
		else {
			tire->setCharacteristics(maxAccelerationSpeed, maxAccelerationReverseSpeed, frontTireMaxDriveForce, frontTireMaxLateralForce);
			(b2RevoluteJoint*)world->CreateJoint(&bodyJoint);
		}
		bodyJoint.bodyB = tire->rubber;
		tires.push_back(tire);
	}

	void update(int controlState) {

		for (int i = 0; i < tires.size(); i++)
			tires[i]->updateFriction();

		for (int i = 0; i < tires.size(); i++)
			tires[i]->updateDrive(controlState);

		// Steering
		float lockAngle = STEER_LOCK_ANGLE * STEER_MOVEMENT_PER_SECOND;
		float turnSpeedPerSec = 160 * STEER_MOVEMENT_PER_SECOND;
		float turnPerTimeStep = turnSpeedPerSec / 60.0f;
		float desiredAngle = 0;
		switch (controlState & (LEFT | RIGHT)) {
		case LEFT:  
			desiredAngle = lockAngle;  
			break;
		case RIGHT: 
			desiredAngle = -lockAngle; 
			break;
		}
		float angleNow = frontLeftJoint->GetJointAngle();
		float angleToTurn = desiredAngle - angleNow;
		angleToTurn = b2Clamp(angleToTurn, -turnPerTimeStep, turnPerTimeStep);
		float newAngle = angleNow + angleToTurn;
		frontLeftJoint->SetLimits(newAngle, newAngle);
		frontRightJoint->SetLimits(newAngle, newAngle);
	}

};