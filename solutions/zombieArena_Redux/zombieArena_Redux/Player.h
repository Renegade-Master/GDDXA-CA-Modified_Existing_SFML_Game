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

class Player : public PlayerCharacter {
public:
	//	Constructor
	Player(SoundBoard& audio);

	// Call this at the end of every game
	void resetPlayerStats();

	void spawn(float posX, float posY);
	void update(sf::Time elapsedTime);
	sf::String getClassName() { return(sf::String("PlayerCharacter::Player")); };

	bool onHit(sf::Time timeHit);

	//	Face the Player towards the mouse
	void lookAt(sf::Vector2f mousePosition, sf::Vector2f resolution);

	// Which angle is the player facing
	float getRotation();

	// Give player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);

private:

	// What size is the current arena
	sf::IntRect m_Arena;
};

#endif // PLAYER_H