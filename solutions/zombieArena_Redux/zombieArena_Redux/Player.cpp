/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "Player.h"
#include "TextureHolder.h"

Player::Player() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	// Associate a texture with the sprite
	// !!Watch this space!!
	m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics/player.png"));

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	m_Sprite.setOrigin(25, 25);
}

void Player::resetPlayerStats() {
	m_Speed = START_SPEED;
	m_Health = START_HEALTH;
	m_MaxHealth = START_HEALTH;

	// Prepare the gun and ammo for next game
	currentBullet = 0;
	bulletsSpare = 24;
	bulletsInClip = 6;
	clipSize = 6;
	fireRate = 1;
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize) {
	// Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	// Store the resolution for future use
	/*m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;*/
}

sf::Time Player::getLastHitTime() {
	return m_LastHit;
}

bool Player::hit(sf::Time timeHit) {
	if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {// 2 tenths of second
		m_LastHit = timeHit;
		m_Health -= 10;
		return true;
	}
	else {
		return false;
	}
}

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

float Player::getRotation() {
	return m_Sprite.getRotation();
}

sf::Sprite Player::getSprite() {
	return m_Sprite;
}

int Player::getHealth() {
	return m_Health;
}

void Player::moveLeft() {
	m_LeftPressed = true;
}

void Player::moveRight() {
	m_RightPressed = true;
}

void Player::moveUp() {
	m_UpPressed = true;
}

void Player::moveDown() {
	m_DownPressed = true;
}

void Player::stopLeft() {
	m_LeftPressed = false;
}

void Player::stopRight() {
	m_RightPressed = false;
}

void Player::stopUp() {
	m_UpPressed = false;
}

void Player::stopDown() {
	m_DownPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition, sf::Vector2f resolution) {

	if (m_UpPressed) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed) {
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	// Keep the player in the arena
	if (m_Position.x > m_Arena.width - m_TileSize) {
		m_Position.x = m_Arena.width - m_TileSize;
	}

	if (m_Position.x < m_Arena.left + m_TileSize) {
		m_Position.x = m_Arena.left + m_TileSize;
	}

	if (m_Position.y > m_Arena.height - m_TileSize) {
		m_Position.y = m_Arena.height - m_TileSize;
	}

	if (m_Position.y < m_Arena.top + m_TileSize) {
		m_Position.y = m_Arena.top + m_TileSize;
	}

	// Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - resolution.y / 2,
		mousePosition.x - resolution.x / 2)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed() {
	// 20% speed upgrade
	m_Speed += (START_SPEED * .2);
}

void Player::upgradeHealth() {
	// 20% max health upgrade
	m_MaxHealth += (START_HEALTH * .2);

}

void Player::increaseHealthLevel(int amount) {
	m_Health += amount;

	// But not beyond the maximum
	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
}

