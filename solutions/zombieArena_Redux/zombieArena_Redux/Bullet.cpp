/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "Bullet.h"

/**
*	Default Constructor
*/
Bullet::Bullet(float damage, float speed) {
	this->m_BulletDamage = damage;
	this->m_BulletSpeed = speed;
	this->m_BulletShape.setSize(
		sf::Vector2f(2.0f * damage, 2.0f * damage));
}

/**
*	Fire a Bullet
*/
void Bullet::shoot(sf::Vector2f origin, sf::Vector2f target) {
	
	// Keep track of the bullet
	this->m_InFlight = true;
	this->m_Position = origin;

	// Calculate the gradient of the flight path
	float gradient = (origin.x - target.x) / (origin.y - target.y);

	// Any gradient less than zero needs to be negative
	if (gradient < 0) {
		gradient *= -1;
	}

	// Calculate the ratio between x and t
	float ratioXY = this->m_BulletSpeed / (1 + gradient);

	// Set the "speed" horizontally and vertically
	this->m_BulletDistanceY = ratioXY;
	this->m_BulletDistanceX = ratioXY * gradient;
	
	// Point the bullet in the right direction
	if (target.x < origin.x) {
		this->m_BulletDistanceX *= -1;
	}

	if (target.y < origin.y) {
		this->m_BulletDistanceY *= -1;
	}

	// Finally, assign the results to the
	// member variables
	this->m_XTarget = target.x;
	this->m_YTarget = target.y;

	// Set a max range of 1000 pixels
	float range = 1000;
	this->m_MinX = origin.x - range;
	this->m_MaxX = origin.x + range;
	this->m_MinY = origin.y - range;
	this->m_MaxY = origin.y + range;
	
	// Position the bullet ready to be drawn
	this->m_BulletShape.setPosition(this->m_Position);
}

/**
*	...
*/
void Bullet::update(float elapsedTime) {
	// Update the bullet position variables
	this->m_Position.x += this->m_BulletDistanceX * elapsedTime;
	this->m_Position.y += this->m_BulletDistanceY * elapsedTime;

	// Move the bullet
	this->m_BulletShape.setPosition(this->m_Position);

	// Has the bullet gone out of range?
	if (this->m_Position.x < this->m_MinX || this->m_Position.x > this->m_MaxX ||
		this->m_Position.y < this->m_MinY || this->m_Position.y > this->m_MaxY)	{
		this->m_InFlight = false;
	}
}