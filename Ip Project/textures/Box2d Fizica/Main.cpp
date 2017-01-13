#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
const float SCALE = 30.f;
using namespace std;
void CreateGround(b2World& World, float X, float Y)
{
	b2BodyDef *BodyDef =  new b2BodyDef();
	BodyDef->position = b2Vec2(X / 30.f, Y / 30.f);
	BodyDef->type = b2_staticBody;
	b2Body* Body = World.CreateBody(&(*BodyDef));

	b2PolygonShape *Shape = new b2PolygonShape();
	Shape->SetAsBox((800.f / 2) / SCALE, (16.f / 2) / SCALE); 
	b2FixtureDef *FixtureDef = new b2FixtureDef();
	FixtureDef->density = 0.f; 
	FixtureDef->shape = &(*Shape);
	Body->CreateFixture(&(*FixtureDef));
}
void CreateBox(b2World& World, int MouseX, int MouseY)
{
	b2BodyDef *BodyDef = new b2BodyDef();
	BodyDef->position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
	BodyDef->type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&(*BodyDef));

	b2PolygonShape *Shape = new b2PolygonShape();
	Shape->SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef *FixtureDef = new b2FixtureDef();
	FixtureDef->density = 1.f;
	FixtureDef->friction = 0.7f;
	FixtureDef->shape = &(*Shape);
	Body->CreateFixture(&(*FixtureDef));
}
int main()
{
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
	Window.setFramerateLimit(60);

	b2Vec2 Gravity(0.f, 9.8f);
	b2World World(Gravity);

	sf::Texture GroundTexture;
	sf::Texture BoxTexture;
	GroundTexture.loadFromFile("textures/ground.png");
	BoxTexture.loadFromFile("textures/box.png");

	CreateGround(World, 400.f, 500.f);

	while (Window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			Window.close();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int MouseX = sf::Mouse::getPosition(Window).x;
			int MouseY = sf::Mouse::getPosition(Window).y;
			CreateBox(World, MouseX, MouseY);
		}

		World.Step(1 / 60.f, 8, 3);
		Window.clear(sf::Color::White);
		for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_dynamicBody)
			{
				sf::Sprite Sprite;
				Sprite.setTexture(BoxTexture);
				Sprite.setOrigin(16.f, 16.f);
				Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				Window.draw(Sprite);
			}
			else
			{
				sf::Sprite GroundSprite;
				GroundSprite.setTexture(GroundTexture);
				GroundSprite.setOrigin(400.f, 8.f);
				GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
				GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				Window.draw(GroundSprite);
			}
		}
		Window.display();
	}

	return 0;
}