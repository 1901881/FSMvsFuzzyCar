//#include "imgui/imgui.h"
//#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "RaceTrack.h"

sf::RectangleShape racingLineInit(sf::RenderWindow* window, sf::RectangleShape line, float movementSpeed);
sf::RectangleShape racingLineUpdate(sf::RectangleShape line, sf::RenderWindow* window, float dt, float movementSpeed);
void racingLineRender(sf::RenderWindow* window, sf::RectangleShape line);

int main()
{
	//For Delta Time
	sf::Clock deltaClock;
	float deltaTime;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window Title");

	//ImGui::SFML::Init(window);

	RaceTrack raceTrack(&window);

	/// /////////////////////
	bool circleExists = true;
	float circleRadius = 200.0f;
	int circleSegments = 100;
	float circleColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255, };
	sf::CircleShape shape(circleRadius, circleSegments);
	
	shape.setFillColor(sf::Color((int)(circleColor[0] * 255), (int)(circleColor[1] * 255), (int)(circleColor[2] * 255)));//Color Circle
	shape.setPosition(200, 200); //Center Circle


	//Racing Line
	sf::RectangleShape line;
	float movementSpeed = 1000.0f;
	line = racingLineInit(&window, line, movementSpeed);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//deltaTime = deltaClock.restart().asSeconds();
			//line = racingLineUpdate(line, &window, deltaTime, movementSpeed);

			//ImGui::SFML::Update(window, deltaClock.restart());
			//ImGui::Begin("Window title");
			//ImGui::Text("Window text!");
			//ImGui::Checkbox("Circle", &circleExists);
			//ImGui::SliderFloat("Radius", &circleRadius, 100.0f, 300.0f);
			//ImGui::SliderInt("Segments", &circleSegments, 3.0f, 150.0f);
			//ImGui::ColorEdit3("Color", circleColor);
			//ImGui::End();

			//shape.setRadius(circleRadius);
			//shape.setPointCount(circleSegments);
			//shape.setFillColor(sf::Color((int)(circleColor[0] * 255), (int)(circleColor[1] * 255), (int)(circleColor[2] * 255)));//Color Circle

			//window.clear(sf::Color(18, 33, 43)); //Color Background

			//racingLineRender(&window, line);
			//if (!circleExists)
			//{
			//	window.draw(shape);
			//}
			//
			//ImGui::SFML::Render(window);//Make sure ImGui is the last to render
			//window.display();
		}

		//Calculate delta time. How much time has passed
		//since it was last calculated (in seconds) and restart the clock.
		deltaTime = deltaClock.restart().asSeconds();

		raceTrack.update(deltaTime);
		raceTrack.render(deltaTime);
	}

	//ImGui::SFML::Shutdown();
	return 0;
}

//Need to split this up into seperate functions
sf::RectangleShape racingLineInit(sf::RenderWindow* window, sf::RectangleShape line, float movementSpeed)
{
	//sf::RectangleShape line;
	//float movementSpeed;

	///Will be parameters later//////////
	sf::Vector2f size = sf::Vector2f(5.0f, window->getSize().y);
	sf::Vector2f position = sf::Vector2f(window->getSize().x / 2.0f, 0.0f);
	//////////////////////////////////////

	line.setSize(size);
	line.setOrigin(sf::Vector2f(size.x / 2.0f, 0.0f));
	line.setPosition(position);

	return line;
}

sf::RectangleShape racingLineUpdate(sf::RectangleShape line, sf::RenderWindow* window, float dt, float movementSpeed)
{
	// Move line left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// Ensure the line doesn't exceed the left bound
		if (line.getPosition().x > 10.0f)
		{
			// Move the line 1 unit left
			line.move(sf::Vector2f(-movementSpeed * dt, 0.0f));
		}
	}

	// Move line right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// Ensure the line doesn't exceed the right bound
		if (line.getPosition().x < window->getSize().x - line.getSize().x)
		{
			// Move the line 1 unit right
			line.move(sf::Vector2f(movementSpeed * dt, 0.0f));
		}
	}

	return line;
}

void racingLineRender(sf::RenderWindow* window, sf::RectangleShape line)
{
	window->draw(line);
}