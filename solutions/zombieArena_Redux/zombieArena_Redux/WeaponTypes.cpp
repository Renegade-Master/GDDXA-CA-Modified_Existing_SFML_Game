/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/05	YYYY/MM/DD
*	@description	...
*/

#include "WeaponTypes.h"

/**
*
*/
Unarmed::Unarmed() {

}

/**
*
*/
void Weapon::loadBullets(int amount) {
	for (int i = 0; i < amount; i++) {
		m_Ammo.push_back(forgeBullet());
	}
}

/**
*
*/
Bullet* Weapon::forgeBullet() {
	Bullet* newBullet;

	switch (this->getClassName()) {
	case sf::Uint32("Unarmed"):
		newBullet = new Bullet(0.0f);
		break;
	case sf::Uint32("Pistol"):
		newBullet = new Bullet(1.0f);
		break;
	default:
		//	Not a Weapon
		break;
	}

	return(newBullet);
}