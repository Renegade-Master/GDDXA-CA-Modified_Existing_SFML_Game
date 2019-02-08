/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "SoundBoard.h"

void SoundBoard::initSounds() {
	/**
	*	UI Sounds
	*/
	this->ui_ButtonClickBuffer.loadFromFile("Audio\\");
	this->ui_ButtonClick.setBuffer(this->ui_ButtonClickBuffer);

	/**
	*	Hit Sounds
	*/
	this->hit_UnarmedBuffer.loadFromFile("Audio\\");
	this->hit_Unarmed.setBuffer(this->hit_UnarmedBuffer);

	this->hit_PistolBuffer.loadFromFile("Audio\\");
	this->hit_Pistol.setBuffer(this->hit_PistolBuffer);

	this->hit_AssaultRifleBuffer.loadFromFile("Audio\\");
	this->hit_AssaultRifle.setBuffer(this->hit_AssaultRifleBuffer);

	this->hit_ShotgunBuffer.loadFromFile("Audio\\");
	this->hit_Shotgun.setBuffer(this->hit_ShotgunBuffer);

	this->hit_RPGBuffer.loadFromFile("Audio\\");
	this->hit_RPG.setBuffer(this->hit_RPGBuffer);
	
	this->hit_KillBuffer.loadFromFile("Audio\\");
	this->hit_Kill.setBuffer(this->hit_KillBuffer);

	/**
	*	Firing Sounds
	*/
	this->fire_UnarmedBuffer.loadFromFile("Audio\\");
	this->fire_Unarmed.setBuffer(this->fire_UnarmedBuffer);

	this->fire_PistolBuffer.loadFromFile("Audio\\");
	this->fire_Pistol.setBuffer(this->fire_PistolBuffer);

	this->fire_AssaultRifleBuffer.loadFromFile("Audio\\");
	this->fire_AssaultRifle.setBuffer(this->fire_AssaultRifleBuffer);

	this->fire_ShotgunBuffer.loadFromFile("Audio\\");
	this->fire_Shotgun.setBuffer(this->fire_ShotgunBuffer);

	this->fire_RPGBuffer.loadFromFile("Audio\\");
	this->fire_RPG.setBuffer(this->fire_RPGBuffer);

	/**
	*	Reload Sounds
	*/
	this->reload_SuccessBuffer.loadFromFile("Audio\\");
	this->reload_Success.setBuffer(this->reload_SuccessBuffer);

	this->reload_FailedBuffer.loadFromFile("Audio\\");
	this->reload_Failed.setBuffer(this->reload_FailedBuffer);

	/**
	*	PowerUp Sounds
	*/
	this->powerUp_SpawnBuffer.loadFromFile("Audio\\");
	this->powerUp_Spawn.setBuffer(this->powerUp_SpawnBuffer);

	this->powerUp_PickupBuffer.loadFromFile("Audio\\");
	this->powerUp_Pickup.setBuffer(this->powerUp_PickupBuffer);
}