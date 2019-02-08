/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "SoundBoard.h"

void SoundBoard::initSounds() {
	// Prepare the hit sound
	hitBuffer.loadFromFile(
		"Audio\\IMPACT_Generic_09_Short_mono.wav");
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	splatBuffer.loadFromFile(
		"Audio\\GORE_Splat_Hit_Short_mono.wav");
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	shootBuffer.loadFromFile(
		"Audio\\FIREARM_Handgun_B_FS92_9mm_Fire_Short_Reverb_Tail_RR2_stereo.wav");
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	reloadBuffer.loadFromFile(
		"Audio\\RELOAD_Clicks_Double_mono.wav");
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	reloadFailedBuffer.loadFromFile(
		"Audio\\RELOAD_Dry_Fire_stereo.wav");
	reloadFailed.setBuffer(reloadFailedBuffer);

	// Prepare the powerup sound
	powerupBuffer.loadFromFile(
		"Audio\\CHARGE_Sci-Fi_High_Pass_Sweep_12_Semi_Up_500ms_stereo.wav");
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	pickupBuffer.loadFromFile(
		"Audio\\8BIT_RETRO_Coin_Collect_Two_Note_Deep_Twinkle_mono.wav");
	pickup.setBuffer(pickupBuffer);

	// Prepare the button sound
	buttonClickBuffer.loadFromFile(
		"Audio\\UI_Click_Organic_49_Dry_Mono.wav");
	buttonClick.setBuffer(buttonClickBuffer);
}