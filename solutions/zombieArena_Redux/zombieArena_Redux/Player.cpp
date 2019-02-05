/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "Player.h"
#include "TextureHolder.h"

/**
*	Default Constructor
*/
Player::Player() {
	m_Speed = PLAYER_START_SPEED;
	m_Health = PLAYER_START_HEALTH;
	m_MaxHealth = PLAYER_START_HEALTH;

	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\player.png"));

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(25, 25);
}

/**
*	Reset Player stats for a new round.
*/
void Player::resetPlayerStats() {
	m_Speed = PLAYER_START_SPEED;
	m_Health = PLAYER_START_HEALTH;
	m_MaxHealth = PLAYER_START_HEALTH;

	// Prepare the gun and ammo for next game
	currentBullet = 0;
	bulletsSpare = 24;
	bulletsInClip = 6;
	clipSize = 6;
	fireRate = 1;
}

/**
*	Spawn the Player into the Game.
*/
void Player::spawn(float posX, float posY) {
	// Place the player in the arena
	m_Position.x = posX;
	m_Position.y = posY;
}

/**
*	Handle the Player being Hit.
*/
bool Player::onHit(sf::Time timeHit) {
	//this->m_Health -= 10;

	return(true);
}

/**
*	Reload the Player's weapon.
*/
bool Player::reload() {
	if (bulletsSpare >= clipSize) {
		// Plenty of bullets. Reload.
		bulletsSpare -= (clipSize - bulletsInClip);
		bulletsInClip = clipSize;
		return(true);
	}
	else if (bulletsSpare > 0) {
		// Less than a clip remaining
		bulletsInClip = bulletsSpare;
		bulletsSpare = 0;
		return(true);
	}
	else {
		// NO ARROWS!!
		return(false);
	}
}

/**
*	...
*/
float Player::getRotation() {
	return m_Sprite.getRotation();
}

/**
*	Update Player attributes
*/
void Player::update(sf::Time elapsedTime) {
	//	Call the Super-Class
	this->PlayerCharacter::update(elapsedTime);
}

/**
*	Face the Player towards the mouse.
*/
void Player::lookAt(sf::Vector2f mousePosition, sf::Vector2f resolution) {
	
	// Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - resolution.y / 2,
		mousePosition.x - resolution.x / 2)
		* 180) / 3.141;

	this->m_Sprite.setRotation(angle);
}

/**
*	Allow the Player to run faster.
*/
void Player::upgradeSpeed() {
	// 20% speed upgrade
	m_Speed += (PLAYER_START_SPEED * .2);
}

/**
*	Allow the Player to live longer.
*/
void Player::upgradeHealth() {
	// 20% max health upgrade
	m_MaxHealth += (PLAYER_START_HEALTH * .2);

}

/**
*	Heal the Player.
*/
void Player::increaseHealthLevel(int amount) {
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
}

/**
*	Return the String name of this Class.
*/
sf::String Player::getClassName() {
	return(sf::String("\nPlayerCharacter::Player Class.\n"));
}