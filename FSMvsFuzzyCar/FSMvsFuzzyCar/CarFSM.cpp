#include "CarFSM.h"

CarFSM::CarFSM(sf::RenderWindow* hwnd)
{
	window = hwnd;

	if (!carFSMTexture.loadFromFile("media/RedCar.png"))
	{
		// error...
	}
	carFSMTexture.setSmooth(true);
	carFSMSprite.setTexture(carFSMTexture);
	carFSMSprite.setScale(sf::Vector2f(0.65f, 0.65f));
	carFSMSprite.setOrigin(sf::Vector2f(carFSMTexture.getSize().x / 2.0f, carFSMTexture.getSize().y / 2.0f));
	carFSMSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 3.0f);

	//sf::Vector2f size = ;
	rectCarFSM.setSize(sf::Vector2f(300, 300));
	float rectColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255, };
	rectCarFSM.setFillColor(sf::Color((int)(rectColor[0] * 255), (int)(rectColor[1] * 255), (int)(rectColor[2] * 255)));//Color Circle
	rectCarFSM.setPosition(window->getSize().x / 2.0f, window->getSize().y / 3.0f);


	currentState = CarStates::Centre;

	velocity = 0.0f;
	acceleration = 0.0f;
	distanceFromLine = 0.0f;
	speedModifier = 50000.0f;
}

CarFSM::~CarFSM()
{
}

void CarFSM::Update(float dt)
{
	MoveCar(dt);
}

void CarFSM::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void CarFSM::MoveCar(float dt)
{
	// Change state of car
	// Depending on distance from line
	// And current speed
	distanceFromLine = linePosition.x - carFSMSprite.getPosition().x;
	//velocity = distanceFromLine / dt;

	//distanceFromLine = linePosition.x - rectCarFSM.getPosition().x;
	distanceFromLine /= window->getSize().x / 2.0f;
	velocity = distanceFromLine / (dt);
	velocity /= 60.0f;

	if (distanceFromLine < -0.5f && velocity < -0.5f)
	{
		currentState = CarStates::FarLeft;
		acceleration = 0.15f;
	}
	if (distanceFromLine > -0.5f && distanceFromLine < -0.1f && velocity > -0.5f && velocity < -0.1f)
	{
		currentState = CarStates::Left;
		acceleration = 0.075f;
	}
	if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	{
		currentState = CarStates::Centre;
		acceleration = 0.01f;
	}
	if (distanceFromLine > 0.1f && distanceFromLine < 0.5f && velocity > 0.1f && velocity < 0.5f)
	{
		currentState = CarStates::Right;
		acceleration = 0.075f;
	}
	if (distanceFromLine > 0.5f && velocity > 0.5f)
	{
		currentState = CarStates::FarRight;
		acceleration = 0.15f;
	}

	float moveX = (velocity * acceleration * dt) * speedModifier;

	switch (currentState)
	{
	case CarStates::FarLeft:
		carFSMSprite.move(sf::Vector2f(moveX, 0.0f));

		rectCarFSM.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Left:
		carFSMSprite.move(sf::Vector2f(moveX, 0.0f));

		rectCarFSM.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Centre:
		carFSMSprite.move(sf::Vector2f(moveX, 0.0f));

		rectCarFSM.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Right:
		carFSMSprite.move(sf::Vector2f(moveX, 0.0f));

		rectCarFSM.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::FarRight:
		carFSMSprite.move(sf::Vector2f(moveX, 0.0f));

		rectCarFSM.move(sf::Vector2f(moveX, 0.0f));
		break;
	default:
		break;
	}
}

void CarFSM::Render()
{
	window->draw(carFSMSprite);
	//window->draw(rectCarFSM);
}
