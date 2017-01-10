#include "user.h"



user::user()
{
}


user::~user()
{
}
void user::Initialise(Run data)
{
	userData = data;
}
void user::user_main()
{
	sf::Vector2f myPos = userData.Start(), newPos = myPos, start = myPos;
	double angle, distance;
	int random;
	srand(time(0));

	while (userData.Move(myPos, newPos) || myPos == start) {
		random = rand() % 360000;
		angle = random / 1000.0;
		distance = userData.Get(myPos, angle);
		newPos = userData.translate(myPos, angle, distance);
	}
}
