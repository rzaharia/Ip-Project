#include "Level.h"



bool Level::IsInCurrentRectangle(sf::Vector2i carPosition)
{
	//std::cout << carPosition.x << " " << carPosition.y << "\n";
	//std::cout<< finishLocations[currentRectangle].firstPoint.x << " " << finishLocations[currentRectangle].firstPoint.y << " \n";
	//std::cout << finishLocations[currentRectangle].secondPoint.x << " " << finishLocations[currentRectangle].secondPoint.y << " \n";
	if (carPosition.x >= finishLocations[currentRectangle].firstPoint.x && carPosition.x <= finishLocations[currentRectangle].secondPoint.x &&
		carPosition.y >= finishLocations[currentRectangle].firstPoint.y && carPosition.y <= finishLocations[currentRectangle].secondPoint.y)
		{
			currentRectangle++;
			pointOfNoReturn++;
			return true;
		}
	return false;
}

void Level::Initialise()
{
	std::ifstream f("textures/levels.txt");
	int tempInt; 
	std::string tempString;
	f >> noOfLevels;
	short int tempNoOfLevel = 0;
	for (short int i = 0; i < noOfLevels; i++)
	{
		levelInfo lvl;
		f >> lvl.levelName;
		f >> lvl.levelType;
		levels[tempNoOfLevel++] = lvl;
	}
	f.close();
}
bool Level::Collision(sf::Vector2i carPosition)
{
	if (adminOn == true)
		return false;
	for(short int i=0;i<noOfObstacles;i++)
	if (carPosition.x >= newObstacles[i].firstPoint.x && carPosition.x <= newObstacles[i].secondPoint.x &&
		carPosition.y >= newObstacles[i].firstPoint.y && carPosition.y <= newObstacles[i].secondPoint.y)
			return true;
	return false;
}
/*
void Level::CreateBox(float x, float y, float width, float height)
{
	b2BodyDef *BodyDef = new b2BodyDef();
	BodyDef->position = b2Vec2(x / 30.f, y / 30.f);
	BodyDef->type = b2_staticBody;
	b2Body* Body = game->World->CreateBody(&(*BodyDef));
	b2PolygonShape *Shape = new b2PolygonShape();
	Shape->SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);
	b2FixtureDef *FixtureDef = new b2FixtureDef();
	
	FixtureDef->density = 0.f;  
	FixtureDef->shape = &(*Shape); 
	Body->CreateFixture(&(*FixtureDef));
	bodiesDef.push_back(BodyDef);
	bodies.push_back(Body);
	polygonShapes.push_back(Shape);
	fixtureDefs.push_back(FixtureDef);

	std::cout << x << " " << y << " " << width << " " << height<<"\n";
	sf::Texture newTexture;
	newTexture.create(width/2, height);
	sf::Sprite *sprite = new sf::Sprite();
	sprite->setTexture(newTexture);
	sprite->setOrigin(SCALE * Body->GetPosition().x/2, SCALE * Body->GetPosition().y/2);//(SCALE * tires[i]->rubber->GetPosition().x/2, SCALE * tires[i]->rubber->GetPosition().y/2);
	sprite->setPosition(SCALE * Body->GetPosition().x, SCALE * Body->GetPosition().y);
	sprite->setRotation(Body->GetAngle() * 180 / b2_pi);
}*/

Level::Level()
{
	game = new Input();
	game->car->SetTextures("textures/car.png", "textures/wheel.png");
	Initialise();
}


Level::~Level()
{
}

void Level::LoadLevel()
{
	currentView = currenViewForDraw::gameView;
	currentLevel++;
	index = 0;
	currentRectangle = 0;
	if (currentLevel <= noOfLevels)
	{
		currentMap->Initialise(levels[currentLevel].levelName);
		std::ifstream f("textures/" + levels[currentLevel].levelName + "Objective.txt");
		if (levels[currentLevel].levelType == 1)
		{
			f >> noOfTeleports;
			short int temp = 0;
			for (short int i = 0; i < noOfTeleports; i++)
			{
				Map::Rectangle rec;
				f >> rec.firstPoint.x;
				f >> rec.firstPoint.y;
				f >> rec.secondPoint.x;
				f >> rec.secondPoint.y;
				finishLocations[temp++] = rec;
			}
			temp = 0;
			f >> noOfPoints;
			for (short int i = 0; i < noOfPoints; i++)
			{
				f >> pointOfReturn[temp].x;
				f >> pointOfReturn[temp++].y;
			}
			f >> noOfObstacles;
			temp = 0;
			for (short int i = 0; i < noOfObstacles; i++)
			{
				Map::Rectangle rec;
				f >> rec.firstPoint.x;
				f >> rec.firstPoint.y;
				f >> rec.secondPoint.x;
				f >> rec.secondPoint.y;
				newObstacles[temp++] = rec;
			}
		}
	}
}

void Level::UnloadLevel()
{

}

void Level::Draw(sf::RenderWindow & window)
{
	currentMap->draw(window);
}

void Level::TriggerEvent(Car *&car)
{
	if (currentLevel <= noOfLevels)
	{
		if (levels[currentLevel].levelType == 1)
			if (noOfTeleports > 0)
			{
				if (IsInCurrentRectangle(car->GetPosition()) == true)
				{
					noOfTeleports--;
					if (noOfTeleports > 0)
					{
						sf::Vector2f playerLocation = currentMap->GetPlayerStartPositions();
						car->SetTransform((int)playerLocation.x / SCALE, (int)playerLocation.y / SCALE);
					}
					else std::cout << "You win!";
				}
			}
	}
}

void Level::InitialiseCarLocation()
{
	sf::Vector2f playerLocation = currentMap->GetPlayerStartPositions();
	game->car->SetTransform((int)playerLocation.x / 30, (int)playerLocation.y / 30);
}

void Level::Update(float &scoreValue, float &timerTime)
{
	if (currentMap->isIn(game->car->GetPosition()) == false || Collision(game->car->GetPosition()) == true)
	{
		scoreValue -= 500;
		timerTime += 20;
		game->car->SetTransform(pointOfReturn[currentRectangle].x / SCALE, pointOfReturn[currentRectangle].y / SCALE);
	}
}
