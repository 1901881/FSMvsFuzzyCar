#pragma once
#include <SFML/Graphics.hpp>
class RoadLine
{
public:
	RoadLine(sf::RenderWindow* hwnd, sf::Vector2f size, sf::Vector2f pos, float speed);
	~RoadLine();

	void Update(float dt);
	void HandleInput(float dt);
	sf::Vector2f GetPosition() { return roadLineSprite.getPosition(); };
	void Render();

private:
	sf::RenderWindow* window;
	sf::RectangleShape roadLine;
	float movementSpeed;

	sf::Texture roadLineTexture;
	sf::Sprite roadLineSprite;
};

