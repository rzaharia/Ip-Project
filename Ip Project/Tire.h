#pragma once

enum {
	LEFT = 0x1,
	RIGHT = 0x2,
	UP = 0x4,
	DOWN = 0x8
};

class Tire {
#define DESIRED_TORQUE 15.0f;

public:
	b2Body* rubber;
	std::set<GroundArea*> groundContactAreas;
	float maxLateralForce;
	float maxAccelerationSpeed;
	float maxAccelerationReverseSpeed;
	float maxAccelerationForce;
	float currentTraction;

	Tire(b2World* raceTrack);
	~Tire();

	void setCharacteristics(float maxForwardSpeed, float maxBackwardSpeed, float maxDriveForce, float maxLateralImpulse);

	void addGroundArea(GroundArea* groundArea);
	void removeGroundArea(GroundArea* groundArea);

	b2Vec2 getLateralVelocity();
	b2Vec2 getForwardVelocity();

	void updateTraction();
	void updateFriction();
	void updateDrive(int controlState);
	void updateTurn(int controlState);
};