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
	*	Music Sounds
	*/
	//this->music_MainMenuBuffer.loadFromFile("Audio\\music_MainMenu.ogg");
	this->music_MainMenuBuffer.loadFromFile("Audio\\Phat Planet.ogg");
	this->music_MainMenu.setBuffer(this->music_MainMenuBuffer);

	//this->music_GameBuffer.loadFromFile("Audio\\music_Game.ogg");
	this->music_GameBuffer.loadFromFile("Audio\\1138.ogg");
	this->music_Game.setBuffer(this->music_GameBuffer);

	/**
	*	UI Sounds
	*/
	this->ui_ButtonClickBuffer.loadFromFile("Audio\\ui_ButtonClick.ogg");
	this->ui_ButtonClick.setBuffer(this->ui_ButtonClickBuffer);

	/**
	*	Hit Sounds
	*/
	this->hit_PlayerBuffer.loadFromFile("Audio\\onPlayerHit.ogg");
	this->hit_Player.setBuffer(hit_PlayerBuffer);

	this->hit_UnarmedBuffer.at(0).loadFromFile("Audio\\onEnemyHit_01.ogg");
	this->hit_Unarmed.at(0).setBuffer(this->hit_UnarmedBuffer.at(0));
	this->hit_UnarmedBuffer.at(1).loadFromFile("Audio\\onEnemyHit_02.ogg");
	this->hit_Unarmed.at(1).setBuffer(this->hit_UnarmedBuffer.at(1));

	this->hit_PistolBuffer.loadFromFile("Audio\\hit_Pistol.ogg");
	this->hit_Pistol.setBuffer(this->hit_PistolBuffer);

	this->hit_AssaultRifleBuffer.loadFromFile("Audio\\hit_AssaultRifle.ogg");
	this->hit_AssaultRifle.setBuffer(this->hit_AssaultRifleBuffer);

	this->hit_ShotgunBuffer.loadFromFile("Audio\\hit_Shotgun.ogg");
	this->hit_Shotgun.setBuffer(this->hit_ShotgunBuffer);

	this->hit_RPGBuffer.loadFromFile("Audio\\hit_RPG.ogg");
	this->hit_RPG.setBuffer(this->hit_RPGBuffer);

	this->hit_KillBuffer.at(0).loadFromFile("Audio\\onEnemyDeath_01.ogg");
	this->hit_Kill.at(0).setBuffer(this->hit_KillBuffer.at(0));
	this->hit_KillBuffer.at(1).loadFromFile("Audio\\onEnemyDeath_02.ogg");
	this->hit_Kill.at(1).setBuffer(this->hit_KillBuffer.at(1));
	this->hit_KillBuffer.at(2).loadFromFile("Audio\\onEnemyDeath_03.ogg");
	this->hit_Kill.at(2).setBuffer(this->hit_KillBuffer.at(2));

	/**
	*	Firing Sounds
	*/
	this->fire_UnarmedBuffer.loadFromFile("Audio\\hit_Unarmed.ogg");
	this->fire_Unarmed.setBuffer(this->fire_UnarmedBuffer);

	this->fire_PistolBuffer.loadFromFile("Audio\\fire_Pistol.ogg");
	this->fire_Pistol.setBuffer(this->fire_PistolBuffer);

	this->fire_AssaultRifleBuffer.loadFromFile("Audio\\fire_AssaultRifle.ogg");
	this->fire_AssaultRifle.setBuffer(this->fire_AssaultRifleBuffer);

	this->fire_ShotgunBuffer.loadFromFile("Audio\\fire_Shotgun.ogg");
	this->fire_Shotgun.setBuffer(this->fire_ShotgunBuffer);

	this->fire_RPGBuffer.loadFromFile("Audio\\fire_RPG.ogg");
	this->fire_RPG.setBuffer(this->fire_RPGBuffer);

	/**
	*	Reload Sounds
	*/
	this->reload_SuccessBuffer.loadFromFile("Audio\\reload_Success.ogg");
	this->reload_Success.setBuffer(this->reload_SuccessBuffer);

	this->reload_FailedBuffer.loadFromFile("Audio\\reload_Failed.ogg");
	this->reload_Failed.setBuffer(this->reload_FailedBuffer);

	/**
	*	PowerUp Sounds
	*/
	this->powerUp_SpawnBuffer.loadFromFile("Audio\\powerUp_Spawn.ogg");
	this->powerUp_Spawn.setBuffer(this->powerUp_SpawnBuffer);

	this->powerUp_PickupBuffer.loadFromFile("Audio\\powerUp_Pickup.ogg");
	this->powerUp_Pickup.setBuffer(this->powerUp_PickupBuffer);
}