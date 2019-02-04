/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVIL_H
#define DEVIL_H

#include "PlayerCharacter.h"

class Devil : public PlayerCharacter {
public:
	// Spawn a new Enemy
	/*virtual*/ void spawn(float posX, float posY, int type);

	// Update the Enemy each frame
	/*virtual*/ void update(float elapsedTime, sf::Vector2f playerLocation);

	//	Handle the Enemy being hit
	/*virtual*/ bool onHit(sf::Time timeHit);

	virtual sf::String getClassName();
};

#endif // DEVIL_H