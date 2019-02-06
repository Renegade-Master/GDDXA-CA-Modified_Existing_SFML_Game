/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/05	YYYY/MM/DD
*	@description	...
*/

#include "WeaponTypes.h"

/***-------------***\
|	Weapon Types	|
\***-------------***/

/**
*	Infinite ammo, low damage, very short range.
*/
Unarmed::Unarmed() {
	m_Weapon = WEAPON_TYPES::UNARMED;

	currentBullet = 0;
	bulletsSpare = 0;
	bulletsInClip = 0;
	clipSize = 0;
	fireRate = 0.0f;
}

/**
*	Low fire rate, low damage, infinite ammo.
*/
Pistol::Pistol() {
	m_Weapon = WEAPON_TYPES::PISTOL;

	currentBullet = 0;
	bulletsSpare = INT_MAX;
	bulletsInClip = 12;
	clipSize = 12;
	fireRate = 2.0f;
}

/**
*	Lots of bullets, medium damage, high fire rate.
*/
AssaultRifle::AssaultRifle() {
	m_Weapon = WEAPON_TYPES::ASSAULTRIFLE;

	currentBullet = 0;
	bulletsSpare = 63;
	bulletsInClip = 32;
	clipSize = 32;
	fireRate = 5.0f;
}

/**
*	Fire many bullets in a spread for a shorter distance.
*/
Shotgun::Shotgun() {
	m_Weapon = WEAPON_TYPES::SHOTGUN;

	currentBullet = 0;
	bulletsSpare = 15;
	bulletsInClip = 6;
	clipSize = 6;
	fireRate = 2.0f;
}

/**
*	Fire a single large bullet that affects an area, very limited ammo.
*/
RPG::RPG() {
	m_Weapon = WEAPON_TYPES::RPG;

	currentBullet = 0;
	bulletsSpare = 9;
	bulletsInClip = 1;
	clipSize = 1;
	fireRate = 1.0f;
}

/***-----------------***\
|	Weapon Functions	|
\***-----------------***/

/**
*	Load an amount of bullets into a Weapon.
*/
void Weapon::loadBullets(int amount) {
	for (int i = 0; i < amount; i++) {
		m_Ammo.push_back(forgeBullet());
	}
}

/**
*	Create a new Bullet.
*/
Bullet* Weapon::forgeBullet() {
	Bullet* newBullet;

	switch (this->m_Weapon) {
	case WEAPON_TYPES::UNARMED:
		newBullet = new Bullet(0.0f);
		break;
	case WEAPON_TYPES::PISTOL:
		newBullet = new Bullet(1.0f);
		break;
	case WEAPON_TYPES::ASSAULTRIFLE:
		newBullet = new Bullet(3.0f);
		break;
	case WEAPON_TYPES::SHOTGUN:
		newBullet = new Bullet(5.0f);
		break;
	case WEAPON_TYPES::RPG:
		newBullet = new Bullet(20.0f);
		break;
	default:
		//	Not a Weapon
		newBullet = nullptr;
		break;
	}

	return(newBullet);
}