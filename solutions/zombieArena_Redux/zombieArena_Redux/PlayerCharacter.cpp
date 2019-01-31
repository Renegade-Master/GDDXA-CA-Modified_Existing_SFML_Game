/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/31	YYYY/MM/DD
*	@description	...
*/

#include "PlayerCharacter.h"

sf::FloatRect PlayerCharacter::getPosition() {
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f PlayerCharacter::getCenter() {
	return m_Position;
}

int PlayerCharacter::getHealth() {
	return m_Health;
}

void PlayerCharacter::moveLeft() {
	m_Movement_H = Movement_H::LEFT;
}

void PlayerCharacter::moveRight() {
	m_Movement_H = Movement_H::RIGHT;
}

void PlayerCharacter::moveUp() {
	m_Movement_V = Movement_V::UP;
}

void PlayerCharacter::moveDown() {
	m_Movement_V = Movement_V::DOWN;
}

void PlayerCharacter::stopLeft() {
	m_Movement_H = Movement_H::IDLE;
}

void PlayerCharacter::stopRight() {
	m_Movement_H = Movement_H::IDLE;
}

void PlayerCharacter::stopUp() {
	m_Movement_V = Movement_V::IDLE;
}

void PlayerCharacter::stopDown() {
	m_Movement_V = Movement_V::IDLE;
}

sf::Sprite PlayerCharacter::getSprite() {
	return m_Sprite;
}

sf::Time getLastHitTime() {
	return m_LastHit;
}