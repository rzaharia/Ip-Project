#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const double pi = 3.1415926535897;
const double eps = 0.000000001;

Vector2f translate ( Vector2f p, double angle, double m ) {
    Vector2f pos;
    pos.x = p.x + m * cos ( angle );
    pos.y = p.y + m * sin ( angle );
    return pos;
}

//angle in degree
double Get ( Vector2f pos, double angle ) {
    double l = 0, r = maximumDistanceInMap, m;
    angle  = angle * pi / 180.0;
    Vector2f newPos;

    while ( l + eps < r ) {
        m = ( l + r ) / 2;
        newPos = translate ( pos, angle, m );

        if ( isIn ( newPos ) )
            l = m;
        else
            r = m;
    }

    return m;
}
