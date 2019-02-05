/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVIL_H
#define DEVIL_H

#include "PlayerCharacter.h"

class Devil abstract : public PlayerCharacter {
public:
	// Spawn a new Enemy
	void spawn(float posX, float posY);

	// Update the Enemy each frame
	virtual void update(sf::Time elapsedTime, sf::Vector2f playerLocation);

	//	Handle the Enemy being hit
	virtual bool onHit(sf::Time timeHit);

	virtual sf::String getClassName() = 0 { return(sf::String("Abstract PlayerCharacter::Devil")); };
};

#endif // DEVIL_H