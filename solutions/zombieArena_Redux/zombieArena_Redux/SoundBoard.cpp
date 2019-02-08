/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/08	YYYY/MM/DD
*	@description	Observer Pattern Implementation
*/

#include "SoundBoard.h"

/**
*	Default Constructor
*/
SoundBoard::SoundBoard() {
	initSounds();
}

void SoundBoard::onNotify(SFX sound) {
	switch (sound) {
	/**
	*	UI Sounds
	*/
	case SFX::CLICK_BUTTON:
		this->ui_ButtonClick.play();

	/**
	*	Hit Sounds
	*/
	case SFX::HIT_UNARMED:
		this->hit_Unarmed.play();
		break;
	case SFX::HIT_PISTOL:
		this->hit_Pistol.play();
		break;
	case SFX::HIT_ASSAULTRIFLE:
		this->hit_AssaultRifle.play();
		break;
	case SFX::HIT_SHOTGUN:
		this->hit_Shotgun.play();
		break;
	case SFX::HIT_RPG:
		this->hit_RPG.play();
		break;
	case SFX::HIT_KILL:
		this->hit_Kill.play();
		break;

	/**
	*	Firing Sounds
	*/
	case SFX::FIRE_UNARMED:
		this->fire_Unarmed.play();
		break;
	case SFX::FIRE_PISTOL:
		this->fire_Pistol.play();
		break;
	case SFX::FIRE_ASSAULTRIFLE:
		this->fire_AssaultRifle.play();
		break;
	case SFX::FIRE_SHOTGUN:
		this->fire_Shotgun.play();
		break;
	case SFX::FIRE_RPG:
		this->fire_RPG.play();
		break;

	/**
	*	Reload Sounds
	*/
	case SFX::RELOAD_SUCCESS:
		this->reload_Success.play();
		break;
	case SFX::RELOAD_FAILED:
		this->reload_Failed.play();
		break;

	/**
	*	PowerUp Sounds
	*/
	case SFX::POWERUP_SPAWN:
		this->powerUp_Spawn.play();
		break;
	case SFX::POWERUP_PICKUP:
		this->powerUp_Pickup.play();
		break;
	}
}