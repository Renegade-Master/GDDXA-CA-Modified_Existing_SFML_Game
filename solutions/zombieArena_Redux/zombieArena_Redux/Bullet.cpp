/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "bullet.h"

// The constructor
Bullet::Bullet() {
	this->m_BulletShape.setSize(sf::Vector2f(2, 2));
}

void Bullet::shoot(float startX, float startY,
	float targetX, float targetY) {
	// Keep track of the bullet
	this->m_InFlight = true;
	this->m_Position.x = startX;
	this->m_Position.y = startY;

	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

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
	if (targetX < startX) {
		this->m_BulletDistanceX *= -1;
	}

	if (targetY < startY) {
		this->m_BulletDistanceY *= -1;
	}

	// Finally, assign the results to the
	// member variables
	this->m_XTarget = targetX;
	this->m_YTarget = targetY;

	// Set a max range of 1000 pixels
	float range = 1000;
	this->m_MinX = startX - range;
	this->m_MaxX = startX + range;
	this->m_MinY = startY - range;
	this->m_MaxY = startY + range;
	
	// Position the bullet ready to be drawn
	this->m_BulletShape.setPosition(this->m_Position);
}

void Bullet::stop() {
	this->m_InFlight = false;
}

bool Bullet::isInFlight() {
	return this->m_InFlight;
}

sf::FloatRect Bullet::getPosition() {
	return this->m_BulletShape.getGlobalBounds();
}

sf::RectangleShape Bullet::getShape() {
	return this->m_BulletShape;
}

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