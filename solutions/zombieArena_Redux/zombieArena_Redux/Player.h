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

	// Handle the player getting hit by a zombie
	bool hit(sf::Time timeHit);

	// Reload the currently equipped weapon
	bool reload();

	// How long ago was the player last hit
	sf::Time getLastHitTime();

	// Which angle is the player facing
	float getRotation();

	// The next four functions move the player
	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	// Stop the player moving in a specific direction
	void stopLeft();

	void stopRight();

	void stopUp();

	void stopDown();

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

	// Where is the player
	sf::Vector2f m_Position;

	// Of course we will need a sprite
	sf::Sprite m_Sprite;

	// And a texture
	// !!Watch this space!!
	sf::Texture m_Texture;

	// What is the screen resolution
	sf::Vector2f m_Resolution;

	// What size is the current arena
	sf::IntRect m_Arena;

	// Which directions is the player currently moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
};

#endif // PLAYER_H