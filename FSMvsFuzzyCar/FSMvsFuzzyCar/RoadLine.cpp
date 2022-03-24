#include "RoadLine.h"

RoadLine::RoadLine(sf::RenderWindow* hwnd, sf::Vector2f size, sf::Vector2f pos, float speed)
{
	window = hwnd;
	
	roadLine.setSize(size);
	roadLine.setOrigin(sf::Vector2f(size.x / 2.0f, 0.0f));
	roadLine.setPosition(pos);
	movementSpeed = speed;


	if (!roadLineTexture.loadFromFile("media/BlueCar.png"))
	{
		// error...
	}

	roadLineTexture.setSmooth(true);
	roadLineSprite.setTexture(roadLineTexture);
	roadLineSprite.setScale(sf::Vector2f(0.65f, 0.65f));
	roadLineSprite.setOrigin(sf::Vector2f(roadLineTexture.getSize().x / 2.0f, roadLineTexture.getSize().y / 2.0f));
	roadLineSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 3.5f);
}

RoadLine::~RoadLine()
{
}

void RoadLine::Update(float dt)
{
	HandleInput(dt);
}

void RoadLine::HandleInput(float dt)
{
	// Move line left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// Ensure the line doesn't exceed the left bound
		if (roadLine.getPosition().x > 10.0f)
		{
			// Move the line 1 unit left
			roadLine.move(sf::Vector2f(-movementSpeed * dt, 0.0f));
		}
	}

	// Move line right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Ensure the line doesn't exceed the right bound
		if (roadLine.getPosition().x < window->getSize().x - roadLine.getSize().x)
		{
			// Move the line 1 unit right
			roadLine.move(sf::Vector2f(movementSpeed * dt, 0.0f));
		}
	}
}

void RoadLine::Render()
{
	// Render the racing line
	window->draw(roadLine);
}
