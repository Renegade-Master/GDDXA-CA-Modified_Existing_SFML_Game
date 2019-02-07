/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/07	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

/**
*	Generate new PowerUps for the Round.
*/
void DevilSpawn::generatePowerUps(int count, sf::IntRect* arena) {
	this->powerUps.clear();

	for (int i = 0; i < count; i++) {
		sf::Vector2i spawnLoc = sf::Vector2i(
			(rand() % arena->height - 50) + 50,
			(rand() % arena->width - 50) + 50);

		int type = (rand() % 10);

		this->powerUps.push_back(
			newPowerUp(spawnLoc, type));
	}
}

/**
*	Generate a new PowerUp
*/
PowerUp* DevilSpawn::newPowerUp(sf::Vector2i pos, int type) {
	PowerUp* pUp = nullptr;

	if (type < 4) {
		pUp = new AmmoPowerUp();
	}
	else if (type < 8) {
		pUp = new HealthPowerUp();
	}
	else/* if (type > 8) */{
		pUp = new WeaponPickUp();
	}

	pUp->spawn(pos);

	return(pUp);
}