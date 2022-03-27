#pragma once

#include <SFML/Graphics.hpp>

class CarFSM
{
public:
	CarFSM(sf::RenderWindow* hwnd);
	~CarFSM();

	void Update(float dt);
	void GetLinePosition(sf::Vector2f linePos);
	void MoveCar(float dt);
	void Render();
	float getVelocity() { return velocity; };
	float getDistanceFromLine() { return distanceFromLine; };
	float& getSpeedModifier() { return speed; };
	sf::Sprite getSprite() { return carFSMSprite; };

private:
	sf::RenderWindow* window;

	sf::Texture carFSMTexture;
	sf::Sprite carFSMSprite;




	//changed this to enum class
	enum class CarStates
	{
		Left = 1,
		Centre = 2,
		Right = 3,
	};

	CarStates currentState;

	sf::Vector2f linePosition;

	float velocity;
	float acceleration;
	float distanceFromLine;
	float speed;
};

