#include "SomeFunctions.h"
SomeFunctions::SomeFunctions()
{
}

SomeFunctions::~SomeFunctions()
{
}

void SomeFunctions::initialise(Map theMap)
{
	currentMap = theMap;
}

bool SomeFunctions::haveAttempts()
{
	if (numberOfTries >= maximumNumberOfTries)
		return 0;
	return 1;
}

sf::Vector2f SomeFunctions::translate(sf::Vector2f p, double angle, double distance)
{
	sf::Vector2f pos;
	pos.x = p.x + distance * cos(angle);
	pos.y = p.y + distance * sin(angle);
	return pos;
}

double SomeFunctions::min(double x, double y)
{
	return x < y ? x : y;
}

double SomeFunctions::Get(sf::Vector2f pos, double angle)
{
	if (!haveAttempts())
		return 0;// No more attempts

	if (!currentMap.isIn(pos))
		return -1;// position is outside the map

	numberOfTries++;
	double m, ret = 2000, i = 2000;
	angle = angle * pi / 180.0;
	sf::Vector2f newPos;

	while (i) {
		double l = eps, r = i;

		while (l + eps < r) {
			m = (l + r) / 2;
			newPos = translate(pos, angle, m);

			if (currentMap.isIn(newPos))
				l = m;
			else
				r = m;
		}

		ret = min(ret, m);
		i -= 100;
	}

	return ret;
}

sf::Vector2f SomeFunctions::Start()
{
	return currentMap.GetPlayerStartPositions();
}

double SomeFunctions::dist(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool SomeFunctions::onSegment(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b)
{
	if (dist(a, c) + dist(c, b) == dist(a, b))
		return 1;

	return 0;
}

double SomeFunctions::crossProduct(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b)
{
	return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

bool SomeFunctions::intersects(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
	if (crossProduct(a, b, c)*crossProduct(a, b, d) < 0 && crossProduct(c, d, a)*crossProduct(c, d, b) < 0)
		return 1;

	if (onSegment(a, c, b) || onSegment(a, d, b) || onSegment(c, a, d) || onSegment(c, b, d))
		return 1;

	return 0;
}

void SomeFunctions::doMove(sf::Vector2f, sf::Vector2f)
{
}

bool SomeFunctions::Move(sf::Vector2f myPos, sf::Vector2f newPos)
{
	if (intersects(currentMap.finishLocation[0], currentMap.finishLocation[1], myPos, newPos))
		return 0;

	doMove(myPos, newPos);
	return 1;
}

int SomeFunctions::otherMain()
{
	sf::Vector2f myPos = Start(), newPos = myPos, start = myPos;
	double angle, distance;
	int random;
	srand(time(0));

	while (Move(myPos, newPos) || myPos == start) {
		random = rand() % 360000;
		angle = random / 1000.0;
		distance = Get(myPos, angle);
		newPos = translate(myPos, angle, distance);
	}
	return 0;
}
