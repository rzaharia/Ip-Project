#include "Car.h"


void Car::Initialise(Map theMap)
{
	map = theMap;
}
Car::Car(b2World* world) {

#pragma region Create the car body

	// Create box2d object for a car.
	b2BodyDef bodyCarType;
	bodyCarType.type = b2_dynamicBody;
	chassis = world->CreateBody(&bodyCarType);
	chassis->SetAngularDamping(3);

	// Create a box body for the car.
	b2Vec2 vertices[4];
	vertices[0].Set(20, 0);
	vertices[1].Set(20, 40);
	vertices[2].Set(-20, 40);
	vertices[3].Set(-20, 0);
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 4);
	b2Fixture* fixture = chassis->CreateFixture(&polygonShape, 0.5f);

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
	CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(-0.35f, -0.5f), true);
	// Back right
	CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(0.35f, -0.5f), true);
	// Front left
	CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(-0.35f, 0.5), false);
	// Front right
	CreateTireAndFixItToCarBody(world, bodyJoint, b2Vec2(0.35f, 0.5), false);

#pragma endregion

}

Car::~Car() {
	for (int i = 0; i < tires.size(); i++)
		delete tires[i];
}

void Car::CreateTireAndFixItToCarBody(b2World* world, b2RevoluteJointDef &bodyJoint, b2Vec2 anchorPosition, bool backTireOrNo) {
	Tire* tire = new Tire(world);

	bodyJoint.bodyB = tire->rubber;
	bodyJoint.localAnchorA = anchorPosition;
	if (backTireOrNo) {
		tire->setCharacteristics(maxAccelerationSpeed, maxAccelerationReverseSpeed, backTireMaxDriveForce, backTireMaxLateralForce);
		world->CreateJoint(&bodyJoint);
	}else {
		tire->setCharacteristics(maxAccelerationSpeed, maxAccelerationReverseSpeed, frontTireMaxDriveForce, frontTireMaxLateralForce);
		if(anchorPosition.x<0)
			frontLeftJoint = (b2RevoluteJoint*)world->CreateJoint(&bodyJoint);
		else
			frontRightJoint = (b2RevoluteJoint*)world->CreateJoint(&bodyJoint);
	}
	tires.push_back(tire);
}

void Car::Update(int controlState) {

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

void Car::Draw(sf::RenderWindow & window)
{
	/*bool canMove=1;
	sf::Vector2i pos;
	for (int i = 0; i < 4; i++)
	{
		pos.x = SCALE * tires[i]->rubber->GetPosition().x;
		pos.y = SCALE * tires[i]->rubber->GetPosition().y;
		if (!map.isIn(pos))
			canMove = 0;
	}
	pos.x = SCALE * chassis->GetPosition().x;
	pos.y = SCALE * chassis->GetPosition().y;
	if (!map.isIn(pos))
		canMove = 0;
	if (!canMove)
		return;
	*/ // You destroy car draw!!!!
	for (int i = 0; i < 4; i++)
	{
		sprites[i].setTexture(texture[0]);
		sprites[i].setOrigin(sprites[i].getGlobalBounds().width/2,sprites[i].getGlobalBounds().height/2);//(SCALE * tires[i]->rubber->GetPosition().x/2, SCALE * tires[i]->rubber->GetPosition().y/2);
		sprites[i].setPosition(SCALE * tires[i]->rubber->GetPosition().x, SCALE * tires[i]->rubber->GetPosition().y);
		sprites[i].setRotation(tires[i]->rubber->GetAngle() * 180 / b2_pi);
		window.draw(sprites[i]);
	}
	sprites[4].setTexture(texture[1]);
	sprites[4].setOrigin(sprites[4].getGlobalBounds().width/2,sprites[4].getGlobalBounds().height/2);//(SCALE * chassis->GetPosition().x/2, SCALE * chassis->GetPosition().y/2);
	sprites[4].setPosition(SCALE * chassis->GetPosition().x, SCALE * chassis->GetPosition().y);
	sprites[4].setRotation(chassis->GetAngle() * 180 / b2_pi);
	window.draw(sprites[4]);
}

void Car::SetTextures(std::string pathCarTexture, std::string pathWheelTexture)
{
	texture[1].loadFromFile(pathCarTexture);
	texture[0].loadFromFile(pathWheelTexture);
}

void Car::SetTransform(float x, float y)
{
	chassis->SetTransform(b2Vec2(x, y), chassis->GetAngle());
}

sf::Vector2i Car::GetPosition()
{
	return sf::Vector2i(sf::Vector2i(SCALE * chassis->GetPosition().x, SCALE * chassis->GetPosition().y));
}
