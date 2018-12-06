/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef ZOMBIEARENA_H
#define ZOMBIEARENA_H

#include "Zombie.h"

int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
Zombie* createHorde(int numZombies, sf::IntRect arena);

#endif // ZOMBIEARENA_H