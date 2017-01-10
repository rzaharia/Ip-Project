#include "Run.h"



Run::Run()
{
}
Run::~Run()
{
}
void Run::initialise(Map theMap)
{
	currentMap = theMap;
}
bool Run::haveAttempts()
{
	if (numberOfTries >= maximumNumberOfTries)
		return 0;
	return 1;
}
sf::Vector2f Run::translate(sf::Vector2f p, double angle, double distance)
{
	sf::Vector2f pos;
	pos.x = p.x + distance * cos(angle);
	pos.y = p.y + distance * sin(angle);
	return pos;
}
double Run::min(double x, double y)
{
	return x < y ? x : y;
}

double Run::Get(sf::Vector2f pos, double angle)
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

sf::Vector2f Run::Start()
{
	return currentMap.GetPlayerStartPositions();
}

double Run::dist(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool Run::onSegment(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b)
{
	if (dist(a, c) + dist(c, b) == dist(a, b))
		return 1;

	return 0;
}

double Run::crossProduct(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b)
{
	return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

bool Run::intersects(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d)
{
	if (crossProduct(a, b, c)*crossProduct(a, b, d) < 0 && crossProduct(c, d, a)*crossProduct(c, d, b) < 0)
		return 1;

	if (onSegment(a, c, b) || onSegment(a, d, b) || onSegment(c, a, d) || onSegment(c, b, d))
		return 1;

	return 0;
}

void Run::doMove(sf::Vector2f, sf::Vector2f)
{
}

bool Run::Move(sf::Vector2f myPos, sf::Vector2f newPos)
{
	if (intersects(currentMap.finishLocation[0], currentMap.finishLocation[1], myPos, newPos))
		return 0;

	doMove(myPos, newPos);
	return 1;
}
