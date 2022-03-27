#include "RaceTrack.h"

RaceTrack::RaceTrack(sf::RenderWindow* window)
{
	// Set window and input for the RaceTrackulation
	this->window = window;

	// Set up the racing line
	roadLine = new RoadLine(window, sf::Vector2f(5.0f, window->getSize().y), sf::Vector2f(window->getSize().x / 2.0f, 0.0f), 1000.0f);

	//// Set up the finite state machine car
	carFSM = new CarFSM(window);

	//// Set up the fuzzy logic car
	carFuzzy = new CarFuzzy(window);

	fout.open("systemsTimingsFile.csv");
	//fout.open("FSMvsFuzzyCarsystemsTimingsFile.csv");
	//fout.open("systemsTimingsFile.txt");
}

RaceTrack::~RaceTrack()
{
	fout.close();
}

void RaceTrack::update(float dt)
{
	// Update the racing line
	roadLine->Update(dt);

	//// Give the lines position to the finite state machine car
	carFSM->GetLinePosition(roadLine->GetPosition());

	//// Give the lines position to the fuzzy logic car
	carFuzzy->GetLinePosition(roadLine->GetPosition());

	the_serial_clock::time_point finiteStart = the_serial_clock::now();
	//// Update the finite state machine car
	carFSM->Update(dt);
	the_serial_clock::time_point finiteEnd = the_serial_clock::now();

	the_serial_clock::time_point fuzzyStart = the_serial_clock::now();
	//// Update the fuzzy logic car
	carFuzzy->Update(dt);
	the_serial_clock::time_point fuzzyEnd = the_serial_clock::now();

	auto finiteTime = duration_cast<nanoseconds>(finiteEnd - finiteStart).count();

	auto fuzzyTime = duration_cast<nanoseconds>(fuzzyEnd - fuzzyStart).count();

	//fout << "burger" << std::endl;
	fout << "Finite Time (ns): " << "," << finiteTime << "," << "," << "Fuzzy Time (ns): " << "," << fuzzyTime << std::endl;


}

void RaceTrack::gui(float dt)
{
	//sf::Time t = sf::seconds(dt);
	//ImGui::SFML::Update(*window, t);

	// Begin ImGui Window
	//ImGui::Begin("Debug");

	//ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

	/*if (ImGui::CollapsingHeader("Finite Car"))
	{
		ImGui::Image(finiteCar->getSprite());
		ImGui::Text("Velocity: %f", finiteCar->getVelocity());
		ImGui::Text("Distance from line: %f", finiteCar->getDistanceFromLine());
		ImGui::Text("Speed Modifier");
		ImGui::InputFloat("", &finiteCar->getSpeedModifier());
	}

	if (ImGui::CollapsingHeader("Fuzzy Car"))
	{
		ImGui::Image(fuzzyCar->getSprite());
		ImGui::Checkbox("Calculate Values", &fuzzyCar->getCalculateValues());
		ImGui::Text("Velocity: %f", fuzzyCar->getVelocity());
		ImGui::Text("Distance from line: %f", fuzzyCar->getDistanceFromLine());
		if (!fuzzyCar->getCalculateValues())
		{
			ImGui::Text("Range (-1) to (1)");
			ImGui::InputFloat("Given Distance: %f", &fuzzyCar->getGivenDistance());
			ImGui::InputFloat("Given Velocity: %f", &fuzzyCar->getGivenVelocity());
		}
		ImGui::Text("Direction: %f", fuzzyCar->getDirection());
		ImGui::Text("Speed Modifier");
		ImGui::InputFloat("", &fuzzyCar->getSpeedModifier());
	}*/

	// End ImGui Window
	//ImGui::End();

	//ImGui::SFML::Render(*window);
}

void RaceTrack::render(float dt)
{
	beginDraw();

	gui(dt);

	// Draw the racing line
	roadLine->Render();

	// Draw the finite state machine car
	carFSM->Render();

	// Draw the fuzzy logic car
	carFuzzy->Render();

	endDraw();
}

void RaceTrack::beginDraw()
{
	// Set window colour to black when clearing
	window->clear(sf::Color(18, 33, 43)); //Color Background
}

void RaceTrack::endDraw()
{
	window->display();
}