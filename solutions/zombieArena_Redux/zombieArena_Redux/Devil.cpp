/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "Devil.h"
#include "TextureHolder.h"

void Devil::spawn(float posX, float posY, int type) {

	switch (type) {
		case 0:
			// Bloater
			this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/demonEnemy_01.png"));

			this->m_Speed = 40;
			this->m_Health = 5;
			break;

		case 1:
			// Chaser
			this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/chaser_headless.png"));

			this->m_Speed = 70;
			this->m_Health = 1;
			break;

		case 2:
			// Crawler
			this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/crawler.png"));

			this->m_Speed = 20;
			this->m_Health = 3;
			break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	//srand((int)time(0) * seed);
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

bool Devil::onHit(sf::Time timeHit) {
	if (!this->isAlive()) {
		// dead
		this->m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics\\blood.png"));

		return(true);
	}

	// injured but not dead yet
	return false;
}

void Devil::update(sf::Time elapsedTime, sf::Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > this->m_Position.x)	{
		this->m_Position.x += this->m_Speed * elapsedTime.asSeconds();
	}

	if (playerY > this->m_Position.y)	{
		this->m_Position.y += this->m_Speed * elapsedTime.asSeconds();
	}

	if (playerX < this->m_Position.x)	{
		this->m_Position.x -= this->m_Speed * elapsedTime.asSeconds();
	}

	if (playerY < this->m_Position.y)	{
		this->m_Position.y -= this->m_Speed * elapsedTime.asSeconds();
	}

	// Move the sprite
	this->m_Sprite.setPosition(this->m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - this->m_Position.y,
		playerX - this->m_Position.x)
		* 180) / 3.141;

	this->m_Sprite.setRotation(angle);
}

/**
*	Return the String name of this Class.
*/
sf::String Devil::getClassName() {
	return(sf::String("\nPlayerCharacter::Devil Class.\n"));
}
