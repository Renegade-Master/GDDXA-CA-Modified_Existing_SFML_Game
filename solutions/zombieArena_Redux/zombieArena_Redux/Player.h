/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "PlayerCharacter.h"

class Player : public PlayerCharacter{
public:
	//	Constructor
	Player();

	// Call this at the end of every game
	void resetPlayerStats();

	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);

	// Reload the currently equipped weapon
	bool reload();

	// Which angle is the player facing
	float getRotation();

	// We will call this function once every frame
	void update(float elapsedTime, sf::Vector2i mousePosition, sf::Vector2f resolution);

	// Give player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);

	// Player Ammunition
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;

private:

	// What size is the current arena
	sf::IntRect m_Arena;
};

#endif // PLAYER_H