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

//class DevilSpawn {
//public:
	int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
	std::vector<Devil> createHorde(int numDevils, sf::IntRect arena);
//};

#endif // DEVILSPAWN_H