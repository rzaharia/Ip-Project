#include<cmath>
#include<cstdlib>
#include<ctime>
#include <SFML/Graphics.hpp>
#include "Map.h"
using namespace sf;

double Get(Vector2f , double);
Vector2f Start();
bool Move(Vector2f , Vector2f);
Vector2f translate(Vector2f, double, double);
void doMove(Vector2f, Vector2f);
