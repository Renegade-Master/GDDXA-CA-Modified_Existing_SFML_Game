/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "PowerUp.h"

//PowerUp::PowerUp() {
//	//ctor
//}

PowerUp::PowerUp() {
	this->m_Sprite.setOrigin(25, 25);

	this->m_SecondsToLive = START_SECONDS_TO_LIVE;
	this->m_SecondsToWait = START_WAIT_TIME;
}

void PowerUp::spawn(sf::Vector2i pos) {
	// Spawn at a random location
	int x = (rand() % pos.x);
	int y = (rand() % pos.y);

	// Not currently spawned
	//this->m_Spawned = false;
	this->m_SecondsSinceSpawn = 0;
	this->m_Spawned = true;
	
	this->m_Sprite.setPosition(x, y);
}

void PowerUp::upgrade() {
	// Make them more frequent and last longer
	this->m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	this->m_SecondsToWait -= (START_WAIT_TIME / 10);
}

int PowerUp::activated(PlayerCharacter& pc) {
	this->m_Spawned = false;
	this->m_SecondsSinceDeSpawn = 0;
	return this->m_Value;
}

void PowerUp::update(float elapsedTime) {
	if (this->m_Spawned) {
		this->m_SecondsSinceSpawn += elapsedTime;
	}
	else {
		this->m_SecondsSinceDeSpawn += elapsedTime;
	}
	
	// Do we need to hide a pickup?
	if (this->m_SecondsSinceSpawn > this->m_SecondsToLive && this->m_Spawned)	{
		// Revove the pickup and put it somewhere else
		this->m_Spawned = false;
		this->m_SecondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a pickup
	if (this->m_SecondsSinceDeSpawn > this->m_SecondsToWait && !this->m_Spawned) {
		// spawn the pickup and reset the timer
		spawn(sf::Vector2i(1000, 1000));
	}
}

AmmoPowerUp::AmmoPowerUp() {
	// Associate HEALTHtexture witHEALTHe sprite
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\ammo_pickup.png"));

	// How much is pickup worth
	this->m_Value = AMMO_START_VALUE;
}

HealthPowerUp::HealthPowerUp() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\health_pickup.png"));

	// How much is pickup worth
	this->m_Value = HEALTH_START_VALUE;
}

WeaponPickUp::WeaponPickUp() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\weapon_pickup.png"));

	// How much is pickup worth
	//this->m_Value = HEALTH_START_VALUE;
}

/**
*	Increase the amount of Ammunition restored
*/
void AmmoPowerUp::upgrade() {
	this->m_Value += (AMMO_START_VALUE * .5);
	this->PowerUp::upgrade();
}

/**
*	Increase the amount of Health restored
*/
void HealthPowerUp::upgrade() {
	this->m_Value += (HEALTH_START_VALUE * .5);
	this->PowerUp::upgrade();
}
