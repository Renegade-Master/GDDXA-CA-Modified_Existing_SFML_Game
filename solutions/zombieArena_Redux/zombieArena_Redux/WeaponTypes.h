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
public:
	enum class WEAPON_TYPES { HOLSTERED, PISTOL, ASSAULTRIFLE, SHOTGUN, RPG };
	
	std::vector<Bullet*> m_Ammo;// A collection of Bullets
	int m_currentBullet = 0;	// Bullet currently in chamber
	int m_clipRemaining = 0;	// Bullets left in the current clip
	int m_bulletsReserved;		// Bullets left in pouch
	
	sf::Time getTimeLastFired() { return(m_timeLastFired); };
	void reload();

	Weapon* forgeWeapon(WEAPON_TYPES type);

	void fire(sf::Vector2f origin, sf::Vector2f target, sf::Time currentFrameTime);

protected:
	WEAPON_TYPES m_Weapon = WEAPON_TYPES::HOLSTERED;

	//	Ammunition
	int m_clipSize;			// How many Bullets fit in this clip

	sf::Time fireRate = sf::Time::Zero;			// How fast can Bullets be fired
	sf::Time m_timeLastFired = sf::Time::Zero;

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
