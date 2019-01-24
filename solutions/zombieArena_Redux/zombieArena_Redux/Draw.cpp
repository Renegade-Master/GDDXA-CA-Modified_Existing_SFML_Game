/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::Draw() {
	/***----------***\
	| Draw the Frame |
	\***----------***/

	window.clear();

	if (state == State::PLAYING) {// set the mainView to be displayed in the window
		// And draw everything related to it
		window.setView(mainView);

		// Draw the background
		window.draw(background, &textureBackground);

		// Draw the horde
		for (std::vector<Devil>::iterator it = horde.begin(); it != horde.end(); ++it) {
			window.draw(it->getSprite());
		}

		// Draw the Bullets in flight
		for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
			if (it->isInFlight()) {
				window.draw(it->getShape());
			}
		}

		// Draw the player
		window.draw(player.getSprite());

		// Draw the pickups if currently spawned
		if (ammoPickup.isSpawned()) {
			window.draw(ammoPickup.getSprite());
		}
		if (healthPickup.isSpawned()) {
			window.draw(healthPickup.getSprite());
		}

		//Draw the crosshair - MUST BE DRAWN TO MAINVIEW
		window.draw(sprite_mouse);

		// Draw the MiniMap
		window.setView(miniMapView);

		window.draw(miniMapBorder);

		// Switch to the HUD view
		window.setView(hudView);

		// Draw all the HUD elements
		window.draw(spriteAmmoIcon);
		window.draw(ammoText);
		window.draw(scoreText);
		window.draw(hiScoreText);
		window.draw(healthBar);
		window.draw(waveNumberText);
		window.draw(hordeRemainingText);
	}

	else if (state == State::PAUSED) {
		window.draw(pausedShader);
		window.draw(pausedText);
	}

	else if (state == State::MAIN_MENU) {
		window.setView(mainView);
		window.draw(spriteGameOver);
		window.draw(mainMenuText);

		for (std::list<GUI::Button>::iterator it = mainMenuButtons.begin(); it != mainMenuButtons.end(); ++it) {
			window.draw(*it);
		}
	}

	else if (state == State::LEVELING_UP) {
		window.draw(spriteGameOver);
		window.draw(levelUpText);

		for (std::list<GUI::Button>::iterator it = levelUpButtons.begin(); it != levelUpButtons.end(); ++it) {
			window.draw(*it);
		}
	}

	else if (state == State::SETTINGS) {
		window.setView(mainView);
		window.draw(spriteGameOver);
		window.draw(settingsText);

		for (std::list<GUI::Button>::iterator it = settingsButtons.begin(); it != settingsButtons.end(); ++it) {
			window.draw(*it);
		}
	}

	else if (state == State::GAME_OVER) {
		window.draw(spriteGameOver);
		window.draw(gameOverText);
		window.draw(scoreText);
		window.draw(hiScoreText);

		for (std::list<GUI::Button>::iterator it = gameOverButtons.begin(); it != gameOverButtons.end(); ++it) {
			window.draw(*it);
		}
	}

	window.display();
}