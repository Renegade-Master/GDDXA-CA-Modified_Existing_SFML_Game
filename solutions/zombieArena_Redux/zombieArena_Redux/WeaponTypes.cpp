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

	this->m_clipSize = 0;
	this->fireRate = sf::Time::Zero;

	this->loadBullets(this->m_clipSize);
}

/**
*	Low fire rate, low damage, infinite ammo.
*/
Pistol::Pistol() {
	this->m_Weapon = WEAPON_TYPES::PISTOL;

	this->m_clipSize = 6;
	this->fireRate = sf::Time(sf::milliseconds(500));

	this->loadBullets(this->m_clipSize);
}

/**
*	Lots of bullets, medium damage, high fire rate.
*/
AssaultRifle::AssaultRifle() {
	this->m_Weapon = WEAPON_TYPES::ASSAULTRIFLE;

	this->m_clipSize = 32;
	this->fireRate = sf::Time(sf::milliseconds(200));

	this->loadBullets(this->m_clipSize);
}

/**
*	Fire many bullets in a spread for a shorter distance.
*/
Shotgun::Shotgun() {
	this->m_Weapon = WEAPON_TYPES::SHOTGUN;

	this->m_clipSize = 6;
	this->fireRate = sf::Time(sf::milliseconds(500));

	this->loadBullets(this->m_clipSize);
}

/**
*	Fire a single large bullet that affects an area, very limited ammo.
*/
RPG::RPG() {
	this->m_Weapon = WEAPON_TYPES::RPG;

	this->m_clipSize = 1;
	this->fireRate = sf::Time(sf::milliseconds(1000));

	this->loadBullets(this->m_clipSize);
}

/***-----------------***\
|	Weapon Functions	|
\***-----------------***/

/**
*	Fire a Bullet
*/
void Weapon::fire(sf::Vector2f origin, sf::Vector2f target, sf::Time totalGameTime) {
	if (this->m_Weapon == Weapon::WEAPON_TYPES::HOLSTERED) { return; }

	sf::Time restPeriod = sf::microseconds(std::abs(
			this->m_timeLastFired.asMicroseconds()
			- totalGameTime.asMicroseconds()));

	//	Ready to fire again?
	if (restPeriod > this->fireRate
		&& this->m_clipRemaining > 0
		&& !this->m_Ammo.empty()) {

		this->m_timeLastFired = totalGameTime;
		this->m_Ammo.back()->shoot(origin, target);	//	Shoot a Bullet
		//this->m_Ammo.pop_back();					//	Remove that Bullet

		this->m_clipRemaining--;

		std::cout << "Firing!" << std::endl;
	}
	else {
		//std::cout << "Firing too soon!" << std::endl;
	}
}

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
		std::cout << "Out of AMMO!" << std::endl;
	}
}

/**
*	Load an amount of Bullets into a Weapon.
*/
void Weapon::loadBullets(int amount) {
	//	Provide several Clips worth of Bullets
	amount *= 5;

	for (int i = 0; i < amount; i++) {
		this->m_Ammo.push_back(this->forgeBullet());
	}
	
	this->m_bulletsReserved = amount;
	this->m_clipRemaining = this->m_clipSize;
}

/**
*	Create a new Bullet.
*/
Bullet* Weapon::forgeBullet() {
	Bullet* newBullet;

	switch (this->m_Weapon) {
	case WEAPON_TYPES::HOLSTERED:
		newBullet = new Bullet(0.0f, 1000);
		break;
	case WEAPON_TYPES::PISTOL:
		newBullet = new Bullet(1.0f, 1000);
		break;
	case WEAPON_TYPES::ASSAULTRIFLE:
		newBullet = new Bullet(3.0f, 1000);
		break;
	case WEAPON_TYPES::SHOTGUN:
		newBullet = new Bullet(5.0f, 1000);
		break;
	case WEAPON_TYPES::RPG:
		newBullet = new Bullet(20.0f, 1000);
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