// State to manage the simulation.

#pragma once
//#include "imgui/imgui.h"
//#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>

#include "RoadLine.h"
#include "CarFSM.h"
#include "CarFuzzy.h"

#include <chrono>
#include <fstream>

// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::ofstream;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_serial_clock;

class RaceTrack
{
public:
	RaceTrack(sf::RenderWindow* hwnd);
	~RaceTrack();

	// Functions
	void update(float dt);
	void gui(float dt);
	void render(float dt);

private:
	// Background setup
	sf::RenderWindow* window;

	// Simulation elements
	RoadLine* roadLine;
	CarFSM* carFSM;
	CarFuzzy* carFuzzy;
	
	// Timing variables
	//ofstream application_timings_file;

	// Draw functions
	void beginDraw();
	void endDraw();
};