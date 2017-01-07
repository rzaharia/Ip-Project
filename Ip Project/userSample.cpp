#include "Madness_drivers.h"


int main() {
    Vector2f myPos = Start(), newPos = myPos, start = myPos;
    double angle, distance;
    int random;
    srand(time(0));

    while(Move(myPos, newPos) || myPos == start) {
        random = rand() % 360000;
        angle = random / 1000.0;
        distance = Get(myPos, angle);
        newPos = translate(myPos, angle, distance);
    }

    return 0;
}
