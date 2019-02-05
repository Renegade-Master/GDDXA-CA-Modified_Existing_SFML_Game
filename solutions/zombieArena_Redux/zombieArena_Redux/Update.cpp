/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::Update() {
		/***------------***\
		| Update the Scene |
		\***------------***/

		// Update while Playing
	if (m_gameState == GameState::PLAYING) {
		// Change the mouse to the GAME mouse
		window.setMouseCursorVisible(false);
		texture_mouse = TextureHolder::GetTexture("Graphics\\crosshair.png");
		sprite_mouse.setTexture(texture_mouse);
		sprite_mouse.setOrigin(25, 25);

		// Where is the mouse pointer
		mouseScreenPosition = sf::Mouse::getPosition(window);

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = window.mapPixelToCoords(
			mouseScreenPosition, mainView);

		// Set the crosshair to the mouse world location
		sprite_mouse.setPosition(mouseWorldPosition);

		// Update the player
		m_Player.update(dt);

		// Make a note of the players new position
		sf::Vector2f playerPosition(m_Player.getCenter());

		// Make the view centre around the player				
		mainView.setCenter(m_Player.getCenter());
		miniMapView.setCenter(m_Player.getCenter());

		// Loop through each Devil and update them
		for (std::vector<Devil*>::iterator it = horde.begin(); it != horde.end(); ++it) {
			if ((*it)->isAlive()) {
				(*it)->update(dt, playerPosition);
			}
		}

		// Update any bullets that are in-flight
		for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
			if ((*it)->isInFlight()) {
				(*it)->update(dt.asSeconds());
			}
		}

		// Update the pickups
		healthPickup.update(dt.asSeconds());
		ammoPickup.update(dt.asSeconds());

		// Collision detection
		// Have any horde been shot?
		for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
			for (std::vector<Devil*>::iterator it2 = horde.begin(); it2 != horde.end(); ++it2) {
				if ((*it)->isInFlight() &&
					(*it2)->isAlive()) {
					if ((*it)->getPosition().intersects
					((*it2)->getPosition())) {
						// Stop the bullet
						(*it)->stop();

						// Register the hit and see if it was a kill
						if ((*it2)->onHit(dt)) {
							// Not just a hit but a kill too
							score += 10;
							if (score >= hiScore) {
								hiScore = score;
							}

							numHordeAlive--;

							// When all the horde are dead (again)
							if (numHordeAlive == 0) {
								m_gameState = GameState::LEVELING_UP;
							}
						}

						// Make a splat sound
						splat.play();
					}
				}
			}
		}// End zombie being shot

		// Have any horde touched the player			
		for (std::vector<Devil*>::iterator it = horde.begin(); it != horde.end(); ++it) {
			if (m_Player.getPosition().intersects
			((*it)->getPosition()) && (*it)->isAlive()) {

				if (m_Player.onHit(gameTimeTotal)) {
					// More here later
					hit.play();
				}

				if (m_Player.getHealth() <= 0) {
					m_gameState = GameState::GAME_OVER;

					std::ofstream outputFile("gamedata\\scores.txt");
					outputFile << hiScore;
					outputFile.close();
				}
			}
		}// End player touched

		// Has the player touched health pickup
		if (m_Player.getPosition().intersects
		(healthPickup.getPosition()) && healthPickup.isSpawned()) {
			m_Player.increaseHealthLevel(healthPickup.gotIt());
			// Play a sound
			pickup.play();
		}

		// Has the player touched ammo pickup
		if (m_Player.getPosition().intersects
		(ammoPickup.getPosition()) && ammoPickup.isSpawned()) {
			m_Player.bulletsSpare += ammoPickup.gotIt();
			// Play a sound
			reload.play();
		}

		// size up the health bar
		healthBar.setSize(sf::Vector2f(m_Player.getHealth() * 3, 70));
		healthBar.setOrigin(healthBar.getSize().x / 2, healthBar.getSize().y / 2);

		// Increment the amount of time since the last HUD update
		timeSinceLastUpdate += dt;
		// Increment the number of frames since the last HUD calculation
		framesSinceLastHUDUpdate++;
		// Calculate FPS every fpsMeasurementFrameInterval frames
		if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval) {

			// Update game HUD text
			std::stringstream ssAmmo;
			std::stringstream ssScore;
			std::stringstream ssHiScore;
			std::stringstream ssWave;
			std::stringstream ssHordeAlive;

			// Update the ammo text
			ssAmmo << m_Player.bulletsInClip << "/" << m_Player.bulletsSpare;
			ammoText.setString(ssAmmo.str());

			// Update the score text
			ssScore << "Score:" << score;
			scoreText.setString(ssScore.str());

			// Update the high score text
			ssHiScore << "Hi Score:" << hiScore;
			hiScoreText.setString(ssHiScore.str());

			// Update the wave
			ssWave << "Wave:" << wave;
			waveNumberText.setString(ssWave.str());

			// Update the high score text
			ssHordeAlive << "Horde Size:" << numHordeAlive;
			hordeRemainingText.setString(ssHordeAlive.str());

			framesSinceLastHUDUpdate = 0;
			timeSinceLastUpdate = sf::Time::Zero;
		}// End HUD update

	}// End updating the PLAYING m_gameState

	// Update while in Paused
	else if (m_gameState == GameState::PAUSED) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);
	}

	// Update while in Main Menu
	else if (m_gameState == GameState::MAIN_MENU) {
		mainView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = btnLst_mainMenu.begin(); it != btnLst_mainMenu.end(); ++it) {
			it->update(evnt, gameTimeTotal, window);
		}
	}

	// Update while in Leveling Up
	else if (m_gameState == GameState::LEVELING_UP) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = btnLst_levelUp.begin(); it != btnLst_levelUp.end(); ++it) {
			it->update(evnt, gameTimeTotal, window);
		}
	}

	// Update while in Settings
	else if (m_gameState == GameState::SETTINGS) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);
		
		if (m_currentSettingsPage == SettingsPage::LIST) {
			for (std::list<GUI::Button>::iterator it = btnLst_allSettings.begin(); it != btnLst_allSettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}
		}
		else if (m_currentSettingsPage == SettingsPage::GRAPHICS) {
			for (std::list<GUI::Button>::iterator it = btnLst_graphicsSettings.begin(); it != btnLst_graphicsSettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}

			// Update Settings to Newly set Values
			//window.setSize(sf::Vector2u(resolution));
			//window.setFramerateLimit(m_frameRate);
			//window.setVerticalSyncEnabled(m_vSyncActive);
			//mainView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
			
			std::cout
				<< "Current Resolution:\t" << resolution.x << " x " << resolution.y << std::endl
				<< "Framerate:\t\t" << m_frameRate << std::endl
				<< "V-Sync Status:\t\t" << m_vSyncActive << std::endl << std::endl;;
		}
		else if (m_currentSettingsPage == SettingsPage::AUDIO) {
			for (std::list<GUI::Button>::iterator it = btnLst_audioSettings.begin(); it != btnLst_audioSettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}
		}
		else if (m_currentSettingsPage == SettingsPage::GAMEPLAY) {
			for (std::list<GUI::Button>::iterator it = btnLst_gameplaySettings.begin(); it != btnLst_gameplaySettings.end(); ++it) {
				it->update(evnt, gameTimeTotal, window);
			}
		}
	}

	// Update while in Game Over
	else if (m_gameState == GameState::GAME_OVER) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = btnLst_gameOver.begin(); it != btnLst_gameOver.end(); ++it) {
			it->update(evnt, gameTimeTotal, window);
		}
	}
}