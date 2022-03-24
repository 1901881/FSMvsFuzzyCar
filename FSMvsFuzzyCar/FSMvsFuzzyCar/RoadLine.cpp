#include "RoadLine.h"

RoadLine::RoadLine(sf::RenderWindow* hwnd, sf::Vector2f size, sf::Vector2f pos, float speed)
{
	window = hwnd;
	
	roadLine.setSize(size);
	roadLine.setOrigin(sf::Vector2f(size.x / 2.0f, 0.0f));
	roadLine.setPosition(pos);
	movementSpeed = speed;
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
