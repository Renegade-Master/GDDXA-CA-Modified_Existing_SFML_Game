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

	if (m_gameState == GameState::PLAYING) {
		// set the mainView to be displayed in the window
		window.setView(mainView);

		// Draw the background
		window.draw(background, &textureBackground);

		// Draw the horde
		for (std::vector<Devil*>::iterator it = horde.begin(); it != horde.end(); ++it) {
			window.draw((*it)->getSprite());
		}

		// Draw the Bullets in flight
		for (std::vector<Bullet*>::iterator it = m_Player->m_Weapon->m_Ammo.begin(); it != m_Player->m_Weapon->m_Ammo.end(); ++it) {
			if ((*it)->isInFlight()) {
				window.draw((*it)->getShape());
			}
		}

		// Draw the player
		window.draw(m_Player->getSprite());

		// Draw the pickups if currently spawned
		for (std::vector<PowerUp*>::iterator it = powerUps.begin(); it != powerUps.end(); ++it) {
			if ((*it)->isSpawned()) {
				window.draw((*it)->getSprite());
			}
		}

		//Draw the crosshair - MUST BE DRAWN TO MAINVIEW
		window.draw(sprite_mouse);

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

	else if (m_gameState == GameState::PAUSED) {
		window.draw(pausedShader);
		window.draw(pausedText);
	}

	else if (m_gameState == GameState::MAIN_MENU) {
		window.setView(mainView);
		window.draw(spriteGameOver);
		window.draw(mainMenuText);

		for (std::list<GUI::Button>::iterator it = btnLst_mainMenu.begin(); it != btnLst_mainMenu.end(); ++it) {
			window.draw(*it);
		}
	}

	else if (m_gameState == GameState::LEVELING_UP) {
		window.draw(spriteGameOver);
		window.draw(levelUpText);

		for (std::list<GUI::Button>::iterator it = btnLst_levelUp.begin(); it != btnLst_levelUp.end(); ++it) {
			window.draw(*it);
		}
	}

	else if (m_gameState == GameState::SETTINGS) {
		window.setView(mainView);
		window.draw(spriteGameOver);
		window.draw(settingsText);

		if (m_currentSettingsPage == SettingsPage::LIST) {
			for (std::list<GUI::Button>::iterator it = btnLst_allSettings.begin(); it != btnLst_allSettings.end(); ++it) {
				window.draw(*it);
			}
		}
		else if (m_currentSettingsPage == SettingsPage::GRAPHICS) {
			window.draw(graphicsSettingsText);
			for (std::list<GUI::Button>::iterator it = btnLst_graphicsSettings.begin(); it != btnLst_graphicsSettings.end(); ++it) {
				window.draw(*it);
			}
		}
		else if (m_currentSettingsPage == SettingsPage::AUDIO) {
			for (std::list<GUI::Button>::iterator it = btnLst_audioSettings.begin(); it != btnLst_audioSettings.end(); ++it) {
				window.draw(*it);
			}
		}
		else if (m_currentSettingsPage == SettingsPage::GAMEPLAY) {
			for (std::list<GUI::Button>::iterator it = btnLst_gameplaySettings.begin(); it != btnLst_gameplaySettings.end(); ++it) {
				window.draw(*it);
			}
		}
	}

	else if (m_gameState == GameState::GAME_OVER) {
		window.draw(spriteGameOver);
		window.draw(gameOverText);
		window.draw(scoreText);
		window.draw(hiScoreText);

		for (std::list<GUI::Button>::iterator it = btnLst_gameOver.begin(); it != btnLst_gameOver.end(); ++it) {
			window.draw(*it);
		}
	}

	window.display();
}