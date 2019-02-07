/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef POWERUP_H
#define POWERUP_H

#include "Constants.h"
#include "PlayerCharacter.h"
#include "TextureHolder.h"

/**
*	Abstract Super PowerUp Class.
*/
class PowerUp abstract {
public:
	PowerUp();

	void spawn(sf::Vector2i pos);

	// Check the position of a pickup
	sf::FloatRect getPosition() { return m_Sprite.getGlobalBounds(); };

	// Get the sprite for drawing
	sf::Sprite getSprite() { return m_Sprite; };

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	// Is this pickup currently spawned?
	bool isSpawned() { return m_Spawned; };

	// Get the goodness from the pickup
	int activated(PlayerCharacter& pc);

	// Upgrade the value of each pickup
	virtual void upgrade();

protected:
	// The sprite that represents this pickup
	sf::Sprite m_Sprite;

	// The arena it exists in
	//sf::IntRect m_Arena;

	// How much is this pickup worth?
	int m_Value;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;
};

/**
*	Restores ammo to maximum
*/
class AmmoPowerUp : public PowerUp {
public:
	AmmoPowerUp();
	void upgrade();
};

/**
*	Restores some health
*/
class HealthPowerUp : public PowerUp {
public:
	HealthPowerUp();
	void upgrade();
};

/**
*	Assigns a random new Weapon.
*/
class WeaponPickUp : public PowerUp {
public:
	WeaponPickUp();
};

#endif // POWERUP_H