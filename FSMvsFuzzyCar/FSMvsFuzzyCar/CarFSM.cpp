#include "CarFSM.h"

CarFSM::CarFSM(sf::RenderWindow* hwnd)
{
	window = hwnd;

	if (!carFSMTexture.loadFromFile("media/RedCar.png"))
	{
		// error...
	}
	carFSMSprite.setTexture(carFSMTexture);
	carFSMSprite.setScale(sf::Vector2f(0.65f, 0.65f));
	carFSMSprite.setOrigin(sf::Vector2f(carFSMTexture.getSize().x / 2.0f, carFSMTexture.getSize().y / 2.0f));
	carFSMSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 1.5f);

	currentState = CarStates::Centre;

	velocity = 0.0f;
	acceleration = 0.0f;
	distanceFromLine = 0.0f;
	speed = 30000.0f;
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
	

	
	distanceFromLine /= window->getSize().x;
	velocity = distanceFromLine / (dt);
	velocity /= 60.0f;

	//

	////CarHeavyLeft
	//if (distanceFromLine < -0.5f && velocity < -0.5f)
	//{
	//	currentState = CarStates::HeavyLeft;
	//	acceleration = 0.15f;
	//}
	////Car Left
	//if (distanceFromLine < -0.5f && velocity < -0.1f)
	//{
	//	currentState = CarStates::Left;
	//	acceleration = 0.075f;
	//}
	////Car Centre
	//if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	//{
	//	currentState = CarStates::Centre;
	//	acceleration = 0.01f;
	//}
	////Car Right
	//if (distanceFromLine > 0.1f && velocity > 0.1f)
	//{
	//	currentState = CarStates::Right;
	//	acceleration = 0.075f;
	//}
	////Car Heavy Right
	//if (distanceFromLine > 0.5f && velocity > 0.5f)
	//{
	//	currentState = CarStates::HeavyRight;
	//	acceleration = 0.15f;
	//}

		//CarHeavyLeft
	if (distanceFromLine < -1.0f && velocity < -1.0f)
	{
		currentState = CarStates::HeavyLeft;
		acceleration = 0.15f;
	}
	//Car Left
	if (distanceFromLine < -0.5f && velocity < -0.5f)
	{
		currentState = CarStates::Left;
		acceleration = 0.075f;
	}
	//Car Centre
	if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	{
		currentState = CarStates::Centre;
		acceleration = 0.01f;
	}
	//Car Right
	if (distanceFromLine > 0.5f && velocity > 0.5f)
	{
		currentState = CarStates::Right;
		acceleration = 0.075f;
	}
	//Car Heavy Right
	if (distanceFromLine > 1.0f && velocity > 1.0f)
	{
		currentState = CarStates::HeavyRight;
		acceleration = 0.15f;
	}




	float move = (velocity * acceleration * dt) * speed;

	switch (currentState)
	{
	case CarStates::HeavyLeft:
		carFSMSprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::Left:
		carFSMSprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::Centre:
		carFSMSprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::Right:
		carFSMSprite.move(sf::Vector2f(move, 0.0f));
		break;
	case CarStates::HeavyRight:
		carFSMSprite.move(sf::Vector2f(move, 0.0f));
		break;
	default:
		break;
	}
}

void CarFSM::Render()
{
	window->draw(carFSMSprite);
}
