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
	this->m_Speed = PLAYER_START_SPEED;
	this->m_Health = PLAYER_START_HEALTH;
	this->m_MaxHealth = PLAYER_START_HEALTH;
	this->m_Weapon = this->m_Weapon->forgeWeapon(Weapon::WEAPON_TYPES::PISTOL);

	// Associate a texture with the sprite
	// !!Watch this space!!
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\player.png"));

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	this->m_Sprite.setOrigin(
		m_Sprite.getTextureRect().width / 2,
		m_Sprite.getTextureRect().height / 2);
}

/**
*	Reset Player stats for a new round.
*/
void Player::resetPlayerStats() {
	this->m_Speed = PLAYER_START_SPEED;
	this->m_Health = PLAYER_START_HEALTH;
	this->m_MaxHealth = PLAYER_START_HEALTH;
	this->m_Weapon = this->m_Weapon->forgeWeapon(Weapon::WEAPON_TYPES::PISTOL);
}

/**
*	Spawn the Player into the Game.
*/
void Player::spawn(float posX, float posY) {
	// Place the player in the arena
	this->m_Position.x = posX;
	this->m_Position.y = posY;
}

/**
*	Handle the Player being Hit.
*/
bool Player::onHit(sf::Time timeHit) {
	return(this->PlayerCharacter::onHit(timeHit));
}

/**
*	...
*/
float Player::getRotation() {
	return this->m_Sprite.getRotation();
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