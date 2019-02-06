/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef WEAPONTYPES_H
#define WEAPONTYPES_H

#include "Bullet.h"

class Weapon abstract {
protected:
	enum class WEAPON_TYPES { UNARMED, PISTOL, ASSAULTRIFLE, SHOTGUN, RPG };
	WEAPON_TYPES m_Weapon = WEAPON_TYPES::UNARMED;

	//	Ammunition
	std::vector<Bullet*> m_Ammo;	// A collection of Bullets
	int currentBullet;				// Bullet currently in chamber
	int bulletsSpare;				// Bullets left in pouch
	int bulletsInClip;				// Bullets left in the current clip
	int clipSize;					// How many Bullets fit in this clip
	float fireRate;					// How fast can Bullets be fired

	void loadBullets(int amount);
	Bullet* forgeBullet();

	virtual ~Weapon() = 0 { /*delete m_Ammo;*/ };
	virtual sf::String getClassName() = 0 { return(sf::String("Weapon")); };
};

class Unarmed : public Weapon {
public:
	Unarmed();

	sf::String getClassName() { return(sf::String("Weapon::Unarmed")); };
};

class Pistol : public Weapon {
public:
	Pistol();

	sf::String getClassName() { return(sf::String("Weapon::Pistol")); };
};

class AssaultRifle : public Weapon {
public:
	AssaultRifle();

	sf::String getClassName() { return(sf::String("Weapon::AssaultRifle")); };
};

class Shotgun : public Weapon {
public:
	Shotgun();

	sf::String getClassName() { return(sf::String("Weapon::Shotgun")); };
};

class RPG : public Weapon {
public:
	RPG();

	sf::String getClassName() { return(sf::String("Weapon::RPG")); };
};

#endif // !WEAPONTYPES_H
