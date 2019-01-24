/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::Input() {
	/***--------***\
	| Handle Input |
	\***--------***/

	// Handle events
	while (window.pollEvent(evnt)) {
		// Handle Keyboard Events
		if (evnt.type == sf::Event::KeyPressed) {
			// Pause while Playing
			if (evnt.key.code == sf::Keyboard::Escape &&
				state == State::PLAYING) {
				state = State::PAUSED;
			}

			// Restart while Paused
			else if (evnt.key.code == sf::Keyboard::Return &&
				state == State::PAUSED) {
				state = State::PLAYING;
				// Reset the clock so there isn't a frame jump
				clock.restart();
			}

			// Quit while Paused
			else if (evnt.key.code == sf::Keyboard::Q &&
				state == State::PAUSED) {
				state = State::MAIN_MENU;
			}

			// Go to Main Menu while in Settings
			else if (evnt.key.code == sf::Keyboard::Escape &&
				state == State::SETTINGS) {
				state = State::MAIN_MENU;
			}

			// Spin and zoom the world				
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				mainView.rotate(1.0f);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				mainView.rotate(-1.0f);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				mainView.zoom(.9f);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				mainView.zoom(1.1f);
			}
			// End spinning and zooming

			// Handle Events in PLAYING state
			if (state == State::PLAYING) {
				// Reloading
				if (evnt.key.code == sf::Keyboard::R) {
					if (player.reload()) {
						reload.play();
					}
					else {
						reloadFailed.play();
					}
				}
			} // End Handling Events in PLAYING state
		}
		// Handle Mouse Events
		else if (evnt.type == sf::Event::MouseButtonPressed) {

		}
	}// End event polling

	// Handle controls while playing
	if (state == State::PLAYING) {
		// Handle the pressing and releasing of the WASD keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.moveUp();
		}
		else {
			player.stopUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.moveDown();
		}
		else {
			player.stopDown();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.moveLeft();
		}
		else {
			player.stopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.moveRight();
		}
		else {
			player.stopRight();
		}

		// Fire a bullet
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			if (gameTimeTotal.asMilliseconds()
				- lastPressed.asMilliseconds()
					> 1000 / player.fireRate && player.bulletsInClip > 0) {

				// Pass the centre of the player and the centre of the crosshair
				// to the shoot function
				bullets[player.currentBullet++].shoot(
					player.getCenter().x, player.getCenter().y,
					mouseWorldPosition.x, mouseWorldPosition.y);
				if (player.currentBullet > 99) {
					player.currentBullet = 0;
				}
				lastPressed = gameTimeTotal;
				shoot.play();
				player.bulletsInClip--;
			}
		}// End fire a bullet
	}// End handling controls while playing

	// Handle the Paused controls
	else if (state == State::PAUSED) {

	} // End Paused controls

	// Handle the main menu controls
	else if (state == State::MAIN_MENU) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = mainMenuButtons.begin(); it != mainMenuButtons.end(); ++it) {
				switch (i++) {
				case 0: // Play Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						state = State::LEVELING_UP;
						wave = 0;
						score = 0;

						// Reset the player's stats
						player.resetPlayerStats();
					}
					break;
				case 1: // Settings Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						state = State::SETTINGS;
					}
					break;
				case 2: // Quit Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						window.close();
					}
					break;
				}
			}
		} // End Button Handling
	} // End Main Menu Controls

	// Handle the levelling up state
	else if (state == State::LEVELING_UP) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = levelUpButtons.begin(); it != levelUpButtons.end(); ++it) {
				switch (i++) {
				case 0: // Rate of Fire Upgrade Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();// Increase fire rate
						player.fireRate++;
						state = State::PLAYING;
					}
					break;
				case 1: // Clip Size Upgrade Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();// Increase clip size
						player.clipSize += player.clipSize;
						state = State::PLAYING;
					}
					break;
				case 2: // Health Upgrade Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();// Increase health
						player.upgradeHealth();
						state = State::PLAYING;
					}
					break;
				case 3: // Run Speed Upgrade Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();// Increase speed
						player.upgradeSpeed();
						state = State::PLAYING;
					}
					break;
				case 4: // Health Pickup Upgrade Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						healthPickup.upgrade();
						state = State::PLAYING;
					}
					break;
				case 5: // Ammo Pickup Upgrade Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						ammoPickup.upgrade();
						state = State::PLAYING;
					}
					break;
				case 6: // Back Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						state = State::MAIN_MENU;
					}
					break;
				}
			}
		}
		if (state == State::PLAYING) {
			// Increase the wave number
			wave++;

			// Prepare thelevel
			// We will modify the next two lines later
			arena.width = 500 * wave;
			arena.height = 500 * wave;
			arena.left = 0;
			arena.top = 0;

			// Pass the vertex array by reference 
			// to the createBackground function
			int tileSize = createBackground(background, arena);

			// Spawn the player in the middle of the arena
			player.spawn(arena, resolution, tileSize);

			// Configure the pick-ups
			healthPickup.setArena(arena);
			ammoPickup.setArena(arena);

			// Create a horde of zombies
			hordeSize = 5 * wave;

			// Delete the previously allocated memory (if it exists)
			horde.clear();
			horde = createHorde(hordeSize, arena);
			numHordeAlive = hordeSize;

			// Play the powerup sound
			powerup.play();

			// Reset the clock so there isn't a frame jump
			clock.restart();
		}
	}// End handling controls while levelling up

	// Handle the Settings controls
	else if (state == State::SETTINGS) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = settingsButtons.begin(); it != settingsButtons.end(); ++it) {
				switch (i++) {
				case 0: // Graphics Settings Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						std::cout << "No Graphics Settings Yet." << std::endl;
					}
					break;
				case 1: // GamePlay Settings Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						std::cout << "No Gameplay Settings Yet." << std::endl;
					}
					break;
				case 2: // Audio Settings Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						std::cout << "No Audio Settings Yet." << std::endl;
					}
					break;
				case 3: // Back Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						state = State::MAIN_MENU;
					}
					break;
				}
			}
		} // End Button Handling
	} // End Settings controls

	// Handle the Game Over controls
	else if (state == State::GAME_OVER) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = gameOverButtons.begin(); it != gameOverButtons.end(); ++it) {
				switch (i++) {
				case 0: // Retry Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						state = State::LEVELING_UP;
						wave = 0;
						score = 0;

						// Reset the player's stats
						player.resetPlayerStats();
					}
					break;
				case 1: // Main Menu Button
					if (it->getState() == GUI::State::clicked) {
						buttonClick.play();
						state = State::MAIN_MENU;
					}
					break;
				}
			}
		} // End Button Handling
	} // End Game Over controls
}