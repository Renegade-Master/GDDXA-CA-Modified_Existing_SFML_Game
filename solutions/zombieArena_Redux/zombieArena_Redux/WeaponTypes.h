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
	//	Ammunition
	int currentBullet;
	int bulletsSpare;
	int bulletsInClip;
	int clipSize;
	float fireRate;

	std::vector<Bullet*> m_Ammo;
	void loadBullets(int amount);
	Bullet* forgeBullet();

	virtual sf::Uint32 getClassName() = 0 { return(sf::Uint32("Weapon")); };
};

class Unarmed : public Weapon {
public:
	Unarmed();

	sf::Uint32 getClassName() { return(sf::Uint32("Weapon::Unarmed")); };
};

class Pistol : public Weapon {
public:
	Pistol();

	sf::Uint32 getClassName() { return(sf::Uint32("Weapon::Pistol")); };
};

class AssaultRifle : public Weapon {
public:
	AssaultRifle();

	sf::Uint32 getClassName() { return(sf::Uint32("Weapon::AssaultRifle")); };
};

class Shotgun : public Weapon {
public:
	Shotgun();

	sf::Uint32 getClassName() { return(sf::Uint32("Weapon::Shotgun")); };
};

class RPG : public Weapon {
public:
	RPG();

	sf::Uint32 getClassName() { return(sf::Uint32("Weapon::RPG")); };
};

#endif // !WEAPONTYPES_H
