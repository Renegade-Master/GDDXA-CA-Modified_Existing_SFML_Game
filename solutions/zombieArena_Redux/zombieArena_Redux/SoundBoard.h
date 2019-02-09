/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/08	YYYY/MM/DD
*	@description	Observer Pattern Implementation
*/

#pragma once
#ifndef SOUNDBOARD_H
#define SOUNDBOARD_H

#include "Observer.h"

/**
*	Generic Sound Class
*/
class SoundBoard : public Observer {
public:
	enum class SFX {
		// UI Sounds
		UI_BUTTONCLICK,

		// Hit Sounds
		HIT_PLAYER,
		HIT_UNARMED,
		HIT_PISTOL,
		HIT_ASSAULTRIFLE,
		HIT_SHOTGUN,
		HIT_RPG,
	
		HIT_KILL,

		// Fire Sounds
		FIRE_UNARMED,
		FIRE_PISTOL,
		FIRE_ASSAULTRIFLE,
		FIRE_SHOTGUN,
		FIRE_RPG,

		// Reload Sounds
		RELOAD_SUCCESS,
		RELOAD_FAILED,

		// PowerUp Sounds
		POWERUP_SPAWN,
		POWERUP_PICKUP		
	};

	SoundBoard();
	void initSounds();

	void onNotify(SFX sound);

private:
	// Sound Buffers
	std::vector<sf::SoundBuffer> hit_UnarmedBuffer;
	std::vector<sf::SoundBuffer> hit_KillBuffer;

	sf::SoundBuffer ui_ButtonClickBuffer;

	sf::SoundBuffer hit_PlayerBuffer;
	sf::SoundBuffer hit_PistolBuffer;
	sf::SoundBuffer hit_AssaultRifleBuffer;
	sf::SoundBuffer hit_ShotgunBuffer;
	sf::SoundBuffer hit_RPGBuffer;

	sf::SoundBuffer fire_UnarmedBuffer;
	sf::SoundBuffer fire_PistolBuffer;
	sf::SoundBuffer fire_AssaultRifleBuffer;
	sf::SoundBuffer fire_ShotgunBuffer;
	sf::SoundBuffer fire_RPGBuffer;

	sf::SoundBuffer reload_SuccessBuffer;
	sf::SoundBuffer reload_FailedBuffer;

	sf::SoundBuffer powerUp_SpawnBuffer;
	sf::SoundBuffer powerUp_PickupBuffer;
	
	// Sounds
	sf::Sound ui_ButtonClick;

	sf::Sound hit_Player;
	std::vector<sf::Sound> hit_Unarmed;
	sf::Sound hit_Pistol;
	sf::Sound hit_AssaultRifle;
	sf::Sound hit_Shotgun;
	sf::Sound hit_RPG;

	std::vector<sf::Sound> hit_Kill;

	sf::Sound fire_Unarmed;
	sf::Sound fire_Pistol;
	sf::Sound fire_AssaultRifle;
	sf::Sound fire_Shotgun;
	sf::Sound fire_RPG;

	sf::Sound reload_Success;
	sf::Sound reload_Failed;

	sf::Sound powerUp_Spawn;
	sf::Sound powerUp_Pickup;
};

#endif // !SOUNDBOARD_H
