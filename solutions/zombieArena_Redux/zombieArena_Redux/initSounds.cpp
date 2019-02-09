/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "SoundBoard.h"

void SoundBoard::initSounds() {
	// Initialise Sound Vectors
	hit_UnarmedBuffer = std::vector<sf::SoundBuffer>(2);
	hit_Unarmed = std::vector<sf::Sound>(2);
	hit_KillBuffer = std::vector<sf::SoundBuffer>(3);
	hit_Kill = std::vector<sf::Sound>(3);

	/**
	*	UI Sounds
	*/
	this->ui_ButtonClickBuffer.loadFromFile("Audio\\ui_ButtonClick.wav");
	this->ui_ButtonClick.setBuffer(this->ui_ButtonClickBuffer);

	/**
	*	Hit Sounds
	*/
	this->hit_PlayerBuffer.loadFromFile("Audio\\onPlayerHit.wav");
	this->hit_Player.setBuffer(hit_PlayerBuffer);

	this->hit_UnarmedBuffer.at(0).loadFromFile("Audio\\onEnemyHit_01.wav");
	this->hit_Unarmed.at(0).setBuffer(this->hit_UnarmedBuffer.at(0));
	this->hit_UnarmedBuffer.at(1).loadFromFile("Audio\\onEnemyHit_02.wav");
	this->hit_Unarmed.at(1).setBuffer(this->hit_UnarmedBuffer.at(1));

	this->hit_PistolBuffer.loadFromFile("Audio\\hit_Pistol.wav");
	this->hit_Pistol.setBuffer(this->hit_PistolBuffer);

	this->hit_AssaultRifleBuffer.loadFromFile("Audio\\hit_AssaultRifle.wav");
	this->hit_AssaultRifle.setBuffer(this->hit_AssaultRifleBuffer);

	this->hit_ShotgunBuffer.loadFromFile("Audio\\hit_Shotgun.wav");
	this->hit_Shotgun.setBuffer(this->hit_ShotgunBuffer);

	this->hit_RPGBuffer.loadFromFile("Audio\\hit_RPG.wav");
	this->hit_RPG.setBuffer(this->hit_RPGBuffer);

	this->hit_KillBuffer.at(0).loadFromFile("Audio\\onEnemyDeath_01.wav");
	this->hit_Kill.at(0).setBuffer(this->hit_KillBuffer.at(0));
	this->hit_KillBuffer.at(1).loadFromFile("Audio\\onEnemyDeath_02.wav");
	this->hit_Kill.at(1).setBuffer(this->hit_KillBuffer.at(1));
	this->hit_KillBuffer.at(2).loadFromFile("Audio\\onEnemyDeath_03.wav");
	this->hit_Kill.at(2).setBuffer(this->hit_KillBuffer.at(2));

	/**
	*	Firing Sounds
	*/
	this->fire_UnarmedBuffer.loadFromFile("Audio\\hit_Unarmed.wav");
	this->fire_Unarmed.setBuffer(this->fire_UnarmedBuffer);

	this->fire_PistolBuffer.loadFromFile("Audio\\fire_Pistol.wav");
	this->fire_Pistol.setBuffer(this->fire_PistolBuffer);

	this->fire_AssaultRifleBuffer.loadFromFile("Audio\\fire_AssaultRifle.wav");
	this->fire_AssaultRifle.setBuffer(this->fire_AssaultRifleBuffer);

	this->fire_ShotgunBuffer.loadFromFile("Audio\\fire_Shotgun.wav");
	this->fire_Shotgun.setBuffer(this->fire_ShotgunBuffer);

	this->fire_RPGBuffer.loadFromFile("Audio\\fire_RPG.wav");
	this->fire_RPG.setBuffer(this->fire_RPGBuffer);

	/**
	*	Reload Sounds
	*/
	this->reload_SuccessBuffer.loadFromFile("Audio\\reload_Success.wav");
	this->reload_Success.setBuffer(this->reload_SuccessBuffer);

	this->reload_FailedBuffer.loadFromFile("Audio\\reload_Failed.wav");
	this->reload_Failed.setBuffer(this->reload_FailedBuffer);

	/**
	*	PowerUp Sounds
	*/
	this->powerUp_SpawnBuffer.loadFromFile("Audio\\powerUp_Spawn.wav");
	this->powerUp_Spawn.setBuffer(this->powerUp_SpawnBuffer);

	this->powerUp_PickupBuffer.loadFromFile("Audio\\powerUp_Pickup.wav");
	this->powerUp_Pickup.setBuffer(this->powerUp_PickupBuffer);
}