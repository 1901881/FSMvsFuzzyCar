#pragma once

#include <SFML/Graphics.hpp>
#include "fl/Headers.h"
//#include "fl\Headers.h"

using namespace fl;

class CarFuzzy
{
public:
	CarFuzzy(sf::RenderWindow* hwnd);
	~CarFuzzy();

	void Update(float dt);
	void GetLinePosition(sf::Vector2f linePos);
	void MoveCar(float dt);
	void Render();
	float getDirection() { return dir; };
	float getVelocity() { return velocity; };
	float getDistanceFromLine() { return distanceFromLine; };
	float& getSpeedModifier() { return speedModifier; };
	bool& getCalculateValues() { return calculateValues; };
	float& getGivenVelocity() { return givenVelocity; };
	float& getGivenDistance() { return givenDistance; };
	sf::Sprite getSprite() { return carFuzzySprite; };

private:
	sf::RenderWindow* window;

	fl::Engine* fuzzyEngine;

	sf::Sprite carFuzzySprite;
	sf::Texture carFuzzyTexture;

	enum class CarStates
	{
		FarLeft = 0,
		Left = 1,
		Centre = 2,
		Right = 3,
		FarRight = 4
	};

	CarStates currentState;

	sf::Vector2f linePosition;

	float velocity;
	float distanceFromLine;
	float dir;
	float speedModifier;
	bool calculateValues;
	float givenVelocity;
	float givenDistance;
};

