<<<<<<< HEAD:Ip Project/Get.cpp
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const double pi = 3.1415926535897;
=======
//#include "Madness_drivers.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

Map currentMap;
long double pi = acos(-1);
>>>>>>> 1e1dcc2... Added isIn function in Map.h and made some minor fixes and adjustments:clase alex vechi/Get.cpp
const double eps = 0.000000001;
int numberOfTries, maximumNumberOfTries = 100;
bool haveAttempts() {
    if ( numberOfTries >= maximumNumberOfTries )
        return 0;
    return 1;
}
<<<<<<< HEAD:Ip Project/Get.cpp
Vector2f translate ( Vector2f p, double angle, double m ) {
    Vector2f pos;
    pos.x = p.x + m * cos ( angle );
    pos.y = p.y + m * sin ( angle );
=======
sf::Vector2f translate(sf::Vector2f p, double angle, double distance) {
    sf::Vector2f pos;
    pos.x = p.x + distance * cos(angle);
    pos.y = p.y + distance * sin(angle);
>>>>>>> 1e1dcc2... Added isIn function in Map.h and made some minor fixes and adjustments:clase alex vechi/Get.cpp
    return pos;
}
double min ( double x, double y ) {
    return x < y ? x : y;
}
//angle in degree
<<<<<<< HEAD:Ip Project/Get.cpp
/*
double Get ( Vector2f pos, double angle ) {
    if ( !haveAttempts() )
        return 0;// No more attempts

	if ( !isIn ( pos ) )
=======
double Get(sf::Vector2f pos, double angle) {
    if(!haveAttempts())
        return 0;// No more attempts

    if(!currentMap.isIn(pos))
>>>>>>> 1e1dcc2... Added isIn function in Map.h and made some minor fixes and adjustments:clase alex vechi/Get.cpp
        return -1;// position is outside the map

    numberOfTries++;
    double m, ret = 2000, i = 2000;
    angle  = angle * pi / 180.0;
    sf::Vector2f newPos;

    while ( i ) {
        double l = eps, r = i;

        while ( l + eps < r ) {
            m = ( l + r ) / 2;
            newPos = translate ( pos, angle, m );

<<<<<<< HEAD:Ip Project/Get.cpp
            if ( isIn ( newPos ) )
=======
            if(currentMap.isIn(newPos))
>>>>>>> 1e1dcc2... Added isIn function in Map.h and made some minor fixes and adjustments:clase alex vechi/Get.cpp
                l = m;
            else
                r = m;
        }

        ret = min ( ret, m );
        i -= 100;
    }

    return ret;
<<<<<<< HEAD:Ip Project/Get.cpp
}*/
=======
}

sf::Vector2f Start() {
    return currentMap.GetPlayerStartPositions();
}
double dist(sf::Vector2f a, sf::Vector2f b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
bool onSegment(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b) {
    if(dist(a, c) + dist(c, b) == dist(a, b))
        return 1;

    return 0;
}
double crossProduct(sf::Vector2f a, sf::Vector2f c, sf::Vector2f b) {
    return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}
bool intersects(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c, sf::Vector2f d) {
    if(crossProduct(a, b, c)*crossProduct(a, b, d) < 0 && crossProduct(c, d, a)*crossProduct(c, d, b) < 0)
        return 1;

    if(onSegment(a, c, b) || onSegment(a, d, b) || onSegment(c, a, d) || onSegment(c, b, d))
        return 1;

    return 0;
}
// Move returns 1 if player not finished yet and makes the movement, else returns 0
void doMove(sf::Vector2f, sf::Vector2f)
{

}
bool Move(sf::Vector2f myPos, sf::Vector2f newPos) {
    if(intersects(currentMap.finishLocation[0], currentMap.finishLocation[1], myPos, newPos))
        return 0;

    doMove(myPos, newPos);
    return 1;
}
>>>>>>> 1e1dcc2... Added isIn function in Map.h and made some minor fixes and adjustments:clase alex vechi/Get.cpp
