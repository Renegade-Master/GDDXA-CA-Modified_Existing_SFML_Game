/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "Devil.h"

void Devil::spawn(float posX, float posY) {

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARIANCE) + OFFSET;
	
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	this->m_Speed *= modifier;

	this->m_Position.x = posX;
	this->m_Position.y = posY;

	this->m_Sprite.setOrigin(25, 25);
	this->m_Sprite.setPosition(this->m_Position);
}

bool Devil::onHit(sf::Time timeHit, Bullet* bullet) {
	if (PlayerCharacter::onHit(timeHit)) {
		this->m_Health -= bullet->m_BulletDamage;

		if (!this->isAlive()) {
			// dead
			this->m_Sprite.setTexture(TextureHolder::GetTexture(
				"graphics\\blood.png"));

			return(true);
		}

		// injured but not dead yet
		return false;
	}
}

void Devil::update(sf::Time elapsedTime, sf::Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > this->m_Position.x)	{
		this->m_Movement_H = Movement_H::RIGHT;
	}

	if (playerY > this->m_Position.y)	{
		this->m_Movement_V = Movement_V::DOWN;
	}

	if (playerX < this->m_Position.x)	{
		this->m_Movement_H = Movement_H::LEFT;
	}

	if (playerY < this->m_Position.y)	{
		this->m_Movement_V = Movement_V::UP;
	}

	this->PlayerCharacter::update(elapsedTime);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - this->m_Position.y,
		playerX - this->m_Position.x)
		* 180) / 3.141;

	this->m_Sprite.setRotation(angle);
}
