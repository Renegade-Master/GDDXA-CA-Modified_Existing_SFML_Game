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
	if (state == State::PLAYING) {
		// Change the mouse to the GAME mouse
		window.setMouseCursorVisible(false);
		texture_mouse = TextureHolder::GetTexture("Graphics\\crosshair.png");
		sprite_mouse.setTexture(texture_mouse);
		sprite_mouse.setOrigin(25, 25);
		// Update the delta time
		sf::Time dt = clock.restart();
		// Update the total game time
		gameTimeTotal += dt;
		// Make a decimal fraction of 1 from the delta time
		float dtAsSeconds = dt.asSeconds();

		// Where is the mouse pointer
		mouseScreenPosition = sf::Mouse::getPosition(window);

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = window.mapPixelToCoords(
			mouseScreenPosition, mainView);

		// Set the crosshair to the mouse world location
		sprite_mouse.setPosition(mouseWorldPosition);

		// Update the player
		player.update(dtAsSeconds, mouseScreenPosition, resolution);

		// Make a note of the players new position
		sf::Vector2f playerPosition(player.getCenter());

		// Make the view centre around the player				
		mainView.setCenter(player.getCenter());
		miniMapView.setCenter(player.getCenter());

		// Loop through each Devil and update them
		for (std::vector<Devil>::iterator it = horde.begin(); it != horde.end(); ++it) {
			if (it->isAlive()) {
				it->update(dt.asSeconds(), playerPosition);
			}
		}

		// Update any bullets that are in-flight
		for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
			if (it->isInFlight()) {
				it->update(dtAsSeconds);
			}
		}

		// Update the pickups
		healthPickup.update(dtAsSeconds);
		ammoPickup.update(dtAsSeconds);

		// Collision detection
		// Have any horde been shot?
		for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
			for (std::vector<Devil>::iterator it2 = horde.begin(); it2 != horde.end(); ++it2) {
				if (it->isInFlight() &&
					it2->isAlive()) {
					if (it->getPosition().intersects
					(it2->getPosition())) {
						// Stop the bullet
						it->stop();

						// Register the hit and see if it was a kill
						if (it2->hit()) {
							// Not just a hit but a kill too
							score += 10;
							if (score >= hiScore) {
								hiScore = score;
							}

							numHordeAlive--;

							// When all the horde are dead (again)
							if (numHordeAlive == 0) {
								state = State::LEVELING_UP;
							}
						}

						// Make a splat sound
						splat.play();
					}
				}
			}
		}// End zombie being shot

		// Have any horde touched the player			
		for (std::vector<Devil>::iterator it = horde.begin(); it != horde.end(); ++it) {
			if (player.getPosition().intersects
			(it->getPosition()) && it->isAlive()) {

				if (player.hit(gameTimeTotal)) {
					// More here later
					hit.play();
				}

				if (player.getHealth() <= 0) {
					state = State::GAME_OVER;

					std::ofstream outputFile("gamedata\\scores.txt");
					outputFile << hiScore;
					outputFile.close();
				}
			}
		}// End player touched

		// Has the player touched health pickup
		if (player.getPosition().intersects
		(healthPickup.getPosition()) && healthPickup.isSpawned()) {
			player.increaseHealthLevel(healthPickup.gotIt());
			// Play a sound
			pickup.play();
		}

		// Has the player touched ammo pickup
		if (player.getPosition().intersects
		(ammoPickup.getPosition()) && ammoPickup.isSpawned()) {
			player.bulletsSpare += ammoPickup.gotIt();
			// Play a sound
			reload.play();
		}

		// size up the health bar
		healthBar.setSize(sf::Vector2f(player.getHealth() * 3, 70));
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
			ssAmmo << player.bulletsInClip << "/" << player.bulletsSpare;
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

	}// End updating the PLAYING state

	// Update while in Paused
	else if (state == State::PAUSED) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);
	}

	// Update while in Main Menu
	else if (state == State::MAIN_MENU) {
		mainView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = mainMenuButtons.begin(); it != mainMenuButtons.end(); ++it) {
			it->update(evnt, window);
		}
	}

	// Update while in Leveling Up
	else if (state == State::LEVELING_UP) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = levelUpButtons.begin(); it != levelUpButtons.end(); ++it) {
			it->update(evnt, window);
		}
	}

	// Update while in Settings
	else if (state == State::SETTINGS) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = settingsButtons.begin(); it != settingsButtons.end(); ++it) {
			it->update(evnt, window);
		}
	}

	// Update while in Game Over
	else if (state == State::GAME_OVER) {
		// Change Mouse to Menu Mouse
		window.setMouseCursorVisible(true);

		for (std::list<GUI::Button>::iterator it = gameOverButtons.begin(); it != gameOverButtons.end(); ++it) {
			it->update(evnt, window);
		}
	}
}