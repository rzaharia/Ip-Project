#include "Madness_drivers.h"


int main() {
    Vector2f myPos = Start(), newPos = myPos, start = myPos;
    int i, ok = 1;
    double angle, distance;
    int random;
    srand(time(0));

    while(Move(myPos, newPos) || mypos == start) {
        random = rand() % 360000;
        angle = random / 1000.0;
        distance = Get(mypos, angle);
        newPos = translate(mypos, angle, distance);
    }

    return 0;
}
