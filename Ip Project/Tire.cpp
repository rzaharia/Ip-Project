#include <Box2d.h>
#include <vector>
#include <set>
#include "GroundArea.h"
#include "CarTire.h""
#include "Tire.h"

Tire::Tire(b2World* raceTrack) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	rubber = raceTrack->CreateBody(&bodyDef);
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.75f, 1.75f);
	b2Fixture* fixture = rubber->CreateFixture(&polygonShape, 1);
	fixture->SetUserData(new CarTire());
	rubber->SetUserData(this);
	currentTraction = 1;
}

Tire::~Tire() {
	rubber->GetWorld()->DestroyBody(rubber);
}

void Tire::setCharacteristics(float maxAccelerationSpeed, float maxAccelerationReverseSpeed, float maxAccelerationForce, float maxLateralForce) {
	Tire::maxAccelerationSpeed = maxAccelerationSpeed;
	Tire::maxAccelerationReverseSpeed = maxAccelerationReverseSpeed;
	Tire::maxAccelerationForce = maxAccelerationForce;
	Tire::maxLateralForce = maxLateralForce;
}

void Tire::addGroundArea(GroundArea* groundArea) {
	groundContactAreas.insert(groundArea);
	updateTraction();
}

void Tire::removeGroundArea(GroundArea* groundArea) {
	groundContactAreas.erase(groundArea);
	updateTraction();
}

void Tire::updateTraction() {
	if (groundContactAreas.empty())
		currentTraction = 1;
	else {
		currentTraction = 0;
		std::set<GroundArea*>::iterator it = groundContactAreas.begin();
		while (it != groundContactAreas.end()) {
			GroundArea* groundArea = *it;
			if (groundArea->frictionModifier > currentTraction)
				currentTraction = groundArea->frictionModifier;
			++it;
		}
	}
}

b2Vec2 Tire::getLateralVelocity() {
	b2Vec2 currentRightNormal = rubber->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(currentRightNormal, rubber->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Tire::getForwardVelocity() {
	b2Vec2 currentForwardNormal = rubber->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(currentForwardNormal, rubber->GetLinearVelocity()) * currentForwardNormal;
}

void Tire::updateFriction() {
	b2Vec2 impulse = rubber->GetMass() * -getLateralVelocity();
	if (impulse.Length() > maxLateralForce)
		impulse *= maxLateralForce / impulse.Length();

	rubber->ApplyLinearImpulse(currentTraction * impulse, rubber->GetWorldCenter(), true);
	rubber->ApplyAngularImpulse(currentTraction * 0.1f * rubber->GetInertia() * -rubber->GetAngularVelocity(), true);

	b2Vec2 currentForwardNormal = getForwardVelocity();
	float currentForwardSpeed = currentForwardNormal.Normalize();
	float dragForceMagnitude = -2 * currentForwardSpeed;

	rubber->ApplyForce(currentTraction * dragForceMagnitude * currentForwardNormal, rubber->GetWorldCenter(), true);
}

void Tire::updateDrive(int controlState) {
	float force = 0;
	float desiredSpeed = 0;

	switch (controlState & (UP | DOWN)) {
	case UP:
		desiredSpeed = maxAccelerationSpeed;
		break;
	case DOWN:
		desiredSpeed = maxAccelerationReverseSpeed;
		break;
	default:
		return;
	}

	b2Vec2 currentForwardNormal = rubber->GetWorldVector(b2Vec2(0, 1));
	float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

	if (desiredSpeed > currentSpeed)
		force = maxAccelerationForce;
	else if (desiredSpeed < currentSpeed)
		force = -maxAccelerationForce;
	else
		return;

	rubber->ApplyForce(currentTraction * force * currentForwardNormal, rubber->GetWorldCenter(), true);
}

void Tire::updateTurn(int controlState) {
	float desiredTorque = 0;

	switch (controlState & (LEFT | RIGHT)) {
	case LEFT:
		desiredTorque = DESIRED_TORQUE;
		break;
	case RIGHT:
		desiredTorque = -1.0f * DESIRED_TORQUE;
		break;
	default:
		return;
	}

	rubber->ApplyTorque(desiredTorque, true);
}