/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVILSPAWN_H
#define DEVILSPAWN_H

#include <iostream> // For Debugging
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"
#include "Button.h"
#include "Devil.h"
#include "DevilSpawn.h"
#include "Pickup.h"
#include "Player.h"
#include "TextureHolder.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
Devil* createHorde(int numDevils, sf::IntRect arena);

#endif // DEVILSPAWN_H