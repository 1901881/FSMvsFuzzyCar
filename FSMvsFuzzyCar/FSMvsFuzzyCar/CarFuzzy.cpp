#include "CarFuzzy.h"

CarFuzzy::CarFuzzy(sf::RenderWindow* hwnd)
{
	window = hwnd;

	if (!carFuzzyTexture.loadFromFile("media/BlueCar.png"))
	{
		// error...
	}
	carFuzzyTexture.setSmooth(true);
	carFuzzySprite.setTexture(carFuzzyTexture);
	carFuzzySprite.setScale(sf::Vector2f(0.65f, 0.65f));
	carFuzzySprite.setOrigin(sf::Vector2f(carFuzzyTexture.getSize().x / 2.0f, carFuzzyTexture.getSize().y / 2.0f));
	carFuzzySprite.setPosition(window->getSize().x / 2.0f, window->getSize().y / 1.5f);

	currentState = CarStates::Centre;

	velocity = 0.0f;
	distanceFromLine = 0.0f;
	speedModifier = 1000.0f;
	calculateValues = true;
	givenDistance = 0.0f;
	givenVelocity = 0.0f;

	fuzzyEngine = FisImporter().fromFile("FuzzyCarInferenceSystem.fis");
}

CarFuzzy::~CarFuzzy()
{
}

void CarFuzzy::Update(float dt)
{
	MoveCar(dt);
}

void CarFuzzy::GetLinePosition(sf::Vector2f linePos)
{
	linePosition = linePos;
}

void CarFuzzy::MoveCar(float dt)
{
	// Change state of car
	// Depending on distance from line
	// And current speed
	if (calculateValues)
	{
		distanceFromLine = linePosition.x - carFuzzySprite.getPosition().x;
		distanceFromLine /= window->getSize().x / 2.0f;
		velocity = distanceFromLine / (dt);
		velocity /= 60.0f;
	}
	else if (!calculateValues)
	{
		if (givenDistance >= -1.0f && givenDistance <= 1.0f && givenVelocity >= -1.0f && givenVelocity <= 1.0f)
		{
			distanceFromLine = givenDistance;
			velocity = givenVelocity;
		}
	}

	// Prevent velocity going outwidth the range in the speed graph
	if (velocity < -1.0f)
	{
		velocity = -1.0f;
	}
	else if (velocity > 1.0f)
	{
		velocity = 1.0f;
	}

	/// Engine usage
	fuzzyEngine->setInputValue("Distance", distanceFromLine);
	fuzzyEngine->setInputValue("Speed", velocity);
	fuzzyEngine->process();
	dir = fuzzyEngine->getOutputValue("Direction");


	if (distanceFromLine < -0.5f && velocity < -0.5f)
	{
		currentState = CarStates::FarLeft;
	}
	if (distanceFromLine > -0.5f && distanceFromLine < -0.1f && velocity > -0.5f && velocity < -0.1f)
	{
		currentState = CarStates::Left;
	}
	if (distanceFromLine > -0.1f && distanceFromLine < 0.1f && velocity > -0.1f && velocity < 0.1f)
	{
		currentState = CarStates::Centre;
	}
	if (distanceFromLine > 0.1f && distanceFromLine < 0.5f && velocity > 0.1f && velocity < 0.5f)
	{
		currentState = CarStates::Right;
	}
	if (distanceFromLine > 0.5f && velocity > 0.5f)
	{
		currentState = CarStates::FarRight;
	}

	float moveX = (dir * dt) * speedModifier;

	switch (currentState)
	{
	case CarStates::FarLeft:
		carFuzzySprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Left:
		carFuzzySprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Centre:
		carFuzzySprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::Right:
		carFuzzySprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	case CarStates::FarRight:
		carFuzzySprite.move(sf::Vector2f(moveX, 0.0f));
		break;
	default:
		break;
	}

	if (carFuzzySprite.getPosition().x < 0.0f)
	{
		carFuzzySprite.setPosition(sf::Vector2f(0.0f, carFuzzySprite.getPosition().y));
	}
	if (carFuzzySprite.getPosition().x > window->getSize().x)
	{
		carFuzzySprite.setPosition(sf::Vector2f(window->getSize().x, carFuzzySprite.getPosition().y));
	}
}

void CarFuzzy::Render()
{
	window->draw(carFuzzySprite);
}
