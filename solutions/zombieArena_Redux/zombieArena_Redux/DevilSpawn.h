/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVILSPAWN_H
#define DEVILSPAWN_H

#include <vector>
#include <fstream>
#include <list>
#include <iostream> // For Console Debugging
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"
#include "Button.h"
#include "Devil.h"
#include "DevilSpawn.h"
#include "Pickup.h"
#include "Player.h"
#include "TextureHolder.h"

class DevilSpawn {
public:
	int runGame();

private:
	int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
	std::vector<Devil> createHorde(int numDevils, sf::IntRect arena);
	   
	// The game will always be in one of six states
	enum class State { PLAYING, PAUSED, MAIN_MENU, LEVELING_UP, SETTINGS, GAME_OVER };
	// Start with the MAIN_MENU state
	State state = State::MAIN_MENU;

	// Set the screen resolution and create an SFML window
	sf::Vector2f resolution;
	sf::Vector2f miniRes;

	sf::RenderWindow window;

	// Create an SFML View
	sf::View mainView;
	// Create a view for the HUD
	sf::View hudView;
	// Create a view for the MiniMap
	sf::View miniMapView;
};

#endif // DEVILSPAWN_H