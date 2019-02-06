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
	this->m_Weapon = WEAPON_TYPES::HOLSTERED;

	this->m_currentBullet = 0;
	this->m_bulletsReserved = -1;
	this->m_clipRemaining = 0;
	this->m_clipSize = 0;
	this->fireRate = sf::Time::Zero;
}

/**
*	Low fire rate, low damage, infinite ammo.
*/
Pistol::Pistol() {
	this->m_Weapon = WEAPON_TYPES::PISTOL;

	this->m_currentBullet = 0;
	this->m_bulletsReserved = -1;
	this->m_clipRemaining = 12;
	this->m_clipSize = 12;
	this->fireRate = sf::Time(sf::milliseconds(500));
}

/**
*	Lots of bullets, medium damage, high fire rate.
*/
AssaultRifle::AssaultRifle() {
	this->m_Weapon = WEAPON_TYPES::ASSAULTRIFLE;

	this->m_currentBullet = 0;
	this->m_bulletsReserved = 63;
	this->m_clipRemaining = 32;
	this->m_clipSize = 32;
	this->fireRate = sf::Time(sf::milliseconds(200));
}

/**
*	Fire many bullets in a spread for a shorter distance.
*/
Shotgun::Shotgun() {
	this->m_Weapon = WEAPON_TYPES::SHOTGUN;

	this->m_currentBullet = 0;
	this->m_bulletsReserved = 15;
	this->m_clipRemaining = 6;
	this->m_clipSize = 6;
	this->fireRate = sf::Time(sf::milliseconds(500));
}

/**
*	Fire a single large bullet that affects an area, very limited ammo.
*/
RPG::RPG() {
	this->m_Weapon = WEAPON_TYPES::RPG;

	this->m_currentBullet = 0;
	this->m_bulletsReserved = 9;
	this->m_clipRemaining = 1;
	this->m_clipSize = 1;
	this->fireRate = sf::Time(sf::milliseconds(1000));
}

/***-------------***\
|	Weapon Firing	|
\***-------------***/

/**
*	Fire a Bullet
*/
void Unarmed::fire(sf::Time currentFrameTime) {
	// Melee?
}

/**
*	Fire a Bullet
*/
void Pistol::fire(sf::Time currentFrameTime) {
	this->m_timeSinceFired += currentFrameTime;

	//	Ready to fire again?
	if (this->m_timeSinceFired + currentFrameTime
		> this->fireRate
		&& this->m_clipRemaining > 0) {

		std::cout << "Firing!" << std::endl;

		this->m_timeSinceFired = sf::Time::Zero;
	}
	else {
		std::cout << "Firing too soon!" << std::endl;
	}
}

/**
*	Fire a Bullet
*/
void AssaultRifle::fire(sf::Time currentFrameTime) {

}

/**
*	Fire a Bullet
*/
void Shotgun::fire(sf::Time currentFrameTime) {

}

/**
*	Fire a Bullet
*/
void RPG::fire(sf::Time currentFrameTime) {

}


/***-----------------***\
|	Weapon Functions	|
\***-----------------***/

/**
*	Reload this Weapon.
*/
void Weapon::reload() {
	if (this->m_bulletsReserved >= this->m_clipSize) {
		// Plenty of bullets. Reload.
		this->m_bulletsReserved -= (this->m_clipSize - this->m_clipRemaining);
		this->m_clipRemaining = this->m_clipSize;
	}
	else if (this->m_bulletsReserved > 0) {
		// Less than a clip remaining
		this->m_clipRemaining = this->m_bulletsReserved;
		this->m_bulletsReserved = 0;
	}
	else {
		// NO ARROWS!!
	}
}

/**
*	Load an amount of Bullets into a Weapon.
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
	case WEAPON_TYPES::HOLSTERED:
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

/**
*	Create a new Weapon
*/
Weapon* Weapon::forgeWeapon(WEAPON_TYPES type) {
	Weapon* freshWeapon;

	switch (type) {
	case WEAPON_TYPES::HOLSTERED:
		freshWeapon = new Unarmed();
		break;
	case WEAPON_TYPES::PISTOL:
		freshWeapon = new Pistol();
		break;
	case WEAPON_TYPES::ASSAULTRIFLE:
		freshWeapon = new AssaultRifle();
		break;
	case WEAPON_TYPES::SHOTGUN:
		freshWeapon = new Shotgun();
		break;
	case WEAPON_TYPES::RPG:
		freshWeapon = new RPG();
		break;
	default:
		//	Not a Weapon
		freshWeapon = nullptr;
		break;
	}

	return(freshWeapon);
}