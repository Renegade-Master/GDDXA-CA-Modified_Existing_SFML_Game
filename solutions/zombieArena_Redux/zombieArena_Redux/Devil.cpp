/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "Devil.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

void Devil::spawn(float startX, float startY, int type, int seed) {

	switch (type) {
		case 0:
			// Bloater
			m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/demonEnemy_01.png"));

			m_Speed = 40;
			m_Health = 5;
			break;

		case 1:
			// Chaser
			m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/chaser_headless.png"));

			m_Speed = 70;
			m_Health = 1;
			break;

		case 2:
			// Crawler
			m_Sprite = sf::Sprite(TextureHolder::GetTexture(
				"graphics/crawler.png"));

			m_Speed = 20;
			m_Health = 3;
			break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Devil::hit() {
	m_Health--;

	if (m_Health < 0) {
		// dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

bool Devil::isAlive() {
	return m_Alive;
}

sf::FloatRect Devil::getPosition() {
	return m_Sprite.getGlobalBounds();
}


sf::Sprite Devil::getSprite() {
	return m_Sprite;
}

void Devil::update(float elapsedTime,
	sf::Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > m_Position.x)	{
		m_Position.x = m_Position.x +
			m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)	{
		m_Position.y = m_Position.y +
			m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)	{
		m_Position.x = m_Position.x -
			m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)	{
		m_Position.y = m_Position.y -
			m_Speed * elapsedTime;
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - m_Position.y,
		playerX - m_Position.x)
		* 180) / 3.141;

	m_Sprite.setRotation(angle);
}
