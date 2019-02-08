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
		this->buttonClick.play();

	/**
	*	Hit Sounds
	*/
	case SFX::HIT_UNARMED:
		this->hit.play();
		break;
	case SFX::HIT_PISTOL:
		this->hit.play();
		break;
	case SFX::HIT_ASSAULTRIFLE:
		this->hit.play();
		break;
	case SFX::HIT_SHOTGUN:
		this->hit.play();
		break;
	case SFX::HIT_RPG:
		this->hit.play();
		break;
	case SFX::HIT_KILL:
		this->splat.play();
		break;

	/**
	*	Firing Sounds
	*/
	case SFX::FIRE_UNARMED:
		this->splat.play();
		break;
	case SFX::FIRE_PISTOL:
		this->hit.play();
		break;
	case SFX::FIRE_ASSAULTRIFLE:
		this->hit.play();
		break;
	case SFX::FIRE_SHOTGUN:
		this->hit.play();
		break;
	case SFX::FIRE_RPG:
		this->hit.play();
		break;

	/**
	*	Reload Sounds
	*/
	case SFX::RELOAD_SUCCESS:
		this->reload.play();
		break;
	case SFX::RELOAD_FAILED:
		this->reloadFailed.play();
		break;

	/**
	*	PowerUp Sounds
	*/
	case SFX::POWERUP_SPAWN:
		this->powerup.play();
		break;
	case SFX::POWERUP_PICKUP:
		this->pickup.play();
		break;
	}
}