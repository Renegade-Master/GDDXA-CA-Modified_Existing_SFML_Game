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
		CLICK_BUTTON,

		HIT_UNARMED,
		HIT_PISTOL,
		HIT_ASSAULTRIFLE,
		HIT_SHOTGUN,
		HIT_RPG,
		HIT_KILL,

		FIRE_UNARMED,
		FIRE_PISTOL,
		FIRE_ASSAULTRIFLE,
		FIRE_SHOTGUN,
		FIRE_RPG,

		RELOAD_SUCCESS,
		RELOAD_FAILED,

		POWERUP_SPAWN,
		POWERUP_PICKUP		
	};

	SoundBoard();
	void initSounds();

	void onNotify(SFX sound);

private:
	//virtual void play() = 0;

	// Sound Buffers
	sf::SoundBuffer hitBuffer;	
	sf::SoundBuffer splatBuffer;	
	sf::SoundBuffer shootBuffer;	
	sf::SoundBuffer reloadBuffer;	
	sf::SoundBuffer reloadFailedBuffer;	
	sf::SoundBuffer powerupBuffer;	
	sf::SoundBuffer pickupBuffer;	
	sf::SoundBuffer buttonClickBuffer;
	
	// Sounds
	sf::Sound hit;
	sf::Sound splat;
	sf::Sound shoot;
	sf::Sound reload;
	sf::Sound reloadFailed;
	sf::Sound powerup;
	sf::Sound pickup;
	sf::Sound buttonClick;
};

#endif // !SOUNDBOARD_H
