/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/31	YYYY/MM/DD
*	@description	...
*/

#include "PlayerCharacter.h"

/**
*	...
*/
void PlayerCharacter::spawn(float posX, float posY) {
	//	Function is overridden
}

/**
*
*/
void PlayerCharacter::update(sf::Time elapsedTime) {
	//	Handle Vertical Movements
	if (this->m_Movement_V == Movement_V::UP) {
		this->m_Position.y -= this->m_Speed * elapsedTime.asSeconds();
	}
	else if (this->m_Movement_V == Movement_V::DOWN) {
		this->m_Position.y += this->m_Speed * elapsedTime.asSeconds();
	}

	//	Handle Horizontal Movements
	if (this->m_Movement_H == Movement_H::LEFT) {
		this->m_Position.x -= this->m_Speed * elapsedTime.asSeconds();
	}
	else if (this->m_Movement_H == Movement_H::RIGHT) {
		this->m_Position.x += this->m_Speed * elapsedTime.asSeconds();
	}

	//	Move the Sprite to the new Position
	this->m_Sprite.setPosition(this->m_Position);
}

/**
*	Return the Position (Global Bounds) of the Sprite assigned to this Object.
*/
sf::FloatRect PlayerCharacter::getPosition() {
	return this->m_Sprite.getGlobalBounds();
}

/**
*	...
*/
sf::Vector2f PlayerCharacter::getCenter() {
	return this->m_Position;
}

/**
*	...
*/
int PlayerCharacter::getHealth() {
	return this->m_Health;
}

/**
*	...
*/
sf::Sprite PlayerCharacter::getSprite() {
	return this->m_Sprite;
}

/**
*	...
*/
sf::Time PlayerCharacter::getLastHitTime() {
	return this->m_LastHit;
}

/**
*	Is this PC alive?
*/
bool PlayerCharacter::isAlive() {
	if (this->m_Health > 0) { return true; }
	else { return false; }
}

/**
*	The the Weapon currently held by the PC
*/
void PlayerCharacter::shoot() {
	//this->m_Weapon->fire();
}

/**
*	Should this PC be hit, or has it been too soon?
*/
bool PlayerCharacter::onHit(sf::Time timeHit) {
	if (timeHit.asMilliseconds() - this->m_LastHit.asMilliseconds() > 200) {
		this->m_LastHit = timeHit;
		this->m_Health -= 10;
		
		return(true);
	}
	else {
		return(false);
	}
}