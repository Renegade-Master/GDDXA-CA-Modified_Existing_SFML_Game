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
				m_gameState == GameState::PLAYING) {
				m_gameState = GameState::PAUSED;
			}

			// Restart while Paused
			else if (evnt.key.code == sf::Keyboard::Return &&
				m_gameState == GameState::PAUSED) {
				m_gameState = GameState::PLAYING;
				// Reset the clock so there isn't a frame jump
				m_GameClock.restart();
			}

			// Quit while Paused
			else if (evnt.key.code == sf::Keyboard::Q &&
				m_gameState == GameState::PAUSED) {
				m_gameState = GameState::MAIN_MENU;
			}

			// Go to Main Menu while in Settings
			else if (evnt.key.code == sf::Keyboard::Escape &&
				m_gameState == GameState::SETTINGS) {
				m_gameState = GameState::MAIN_MENU;
			}
		}
		// Handle Mouse Events
		else if (evnt.type == sf::Event::MouseButtonPressed) {

		}
	}// End event polling

	// Handle controls while playing
	if (m_gameState == GameState::PLAYING) {

		cmd = m_InpHand.handleInput(m_FrameTime);

		if (m_Player.m_Weapon->m_Ammo.empty()) {
			m_Player.m_Weapon->forgeWeapon(Weapon::WEAPON_TYPES::PISTOL);
		}

		if (cmd) { 
			cmd->execute(m_Player, sf::Vector2f(mouseWorldPosition), gameTimeTotal);
		}

		m_Player.lookAt(sf::Vector2f(mouseScreenPosition), resolution);

	}// End handling controls while playing

	// Handle the Paused controls
	else if (m_gameState == GameState::PAUSED) {

	} // End Paused controls

	// Handle the main menu controls
	else if (m_gameState == GameState::MAIN_MENU) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = btnLst_mainMenu.begin(); it != btnLst_mainMenu.end(); ++it) {
				switch (i++) {
				case 0: // Play Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						m_gameState = GameState::LEVELING_UP;
						wave = 0;
						score = 0;

						// Reset the player's stats
						m_Player.resetPlayerStats();
					}
					break;
				case 1: // Settings Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						m_gameState = GameState::SETTINGS;
					}
					break;
				case 2: // Quit Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						window.close();
					}
					break;
				}
			}
		} // End Button Handling
	} // End Main Menu Controls

	// Handle the levelling up m_gameState
	else if (m_gameState == GameState::LEVELING_UP) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = btnLst_levelUp.begin(); it != btnLst_levelUp.end(); ++it) {
				switch (i++) {
				case 0: // Rate of Fire Upgrade Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();// Increase fire rate
						//m_Player.fireRate++;
						m_gameState = GameState::PLAYING;
					}
					break;
				case 1: // Clip Size Upgrade Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();// Increase clip size
						//m_Player.m_clipSize += m_Player.m_clipSize;
						m_gameState = GameState::PLAYING;
					}
					break;
				case 2: // Health Upgrade Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();// Increase health
						m_Player.upgradeHealth();
						m_gameState = GameState::PLAYING;
					}
					break;
				case 3: // Run Speed Upgrade Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();// Increase speed
						m_Player.upgradeSpeed();
						m_gameState = GameState::PLAYING;
					}
					break;
				case 4: // Health PowerUp Upgrade Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						healthPickup.upgrade();
						m_gameState = GameState::PLAYING;
					}
					break;
				case 5: // Ammo PowerUp Upgrade Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						ammoPickup.upgrade();
						m_gameState = GameState::PLAYING;
					}
					break;
				case 6: // Back Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						m_gameState = GameState::MAIN_MENU;
					}
					break;
				}
			}
		}
		if (m_gameState == GameState::PLAYING) {
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
			m_Player.spawn(250,50);

			// Configure the pick-ups
			healthPickup.setArena(arena);
			ammoPickup.setArena(arena);

			// Create a horde of zombies
			hordeSize = 5 * wave;

			// Delete the previously allocated memory (if it exists)
			horde.clear();
			createHorde(hordeSize, arena);
			numHordeAlive = hordeSize;

			// Play the powerup sound
			powerup.play();

			// Reset the clock so there isn't a frame jump
			m_GameClock.restart();
		}
	}// End handling controls while levelling up

	// Handle the Settings controls
	else if (m_gameState == GameState::SETTINGS) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			if (m_currentSettingsPage == SettingsPage::LIST) {
				for (std::list<GUI::Button>::iterator it = btnLst_allSettings.begin(); it != btnLst_allSettings.end(); ++it) {
					switch (i++) {
					case 0: // Graphics Settings Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							//std::cout << "No Graphics Settings Yet." << std::endl;
							m_currentSettingsPage = SettingsPage::GRAPHICS;
						}
						break;
					case 1: // Audio Settings Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							//std::cout << "No Gameplay Settings Yet." << std::endl;
							m_currentSettingsPage = SettingsPage::AUDIO;
						}
						break;
					case 2: // GamePlay Settings Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							//std::cout << "No Audio Settings Yet." << std::endl;
							m_currentSettingsPage = SettingsPage::GAMEPLAY;
						}
						break;
					case 3: // Back Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_gameState = GameState::MAIN_MENU;
						}
						break;
					}
				}
			} // End All Settings Page
			else if (m_currentSettingsPage == SettingsPage::GRAPHICS) {
				for (std::list<GUI::Button>::iterator it = btnLst_graphicsSettings.begin(); it != btnLst_graphicsSettings.end(); ++it) {
					switch (i++) {
					case 0: // Fullscreen Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_windowedStatus = sf::Style::Fullscreen;
							resolution = sf::Vector2f(
								sf::VideoMode::getDesktopMode().width,
								sf::VideoMode::getDesktopMode().height);
							refreshWindow();
						}
						break;
					case 1: // Windowed Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_windowedStatus = sf::Style::Default;
							resolution = sf::Vector2f(
								1280,
								720);
							refreshWindow();
						}
						break;
					case 2: // 30 FPS Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_frameRate = 30;
							refreshWindow();
						}
						break;
					case 3: // 60 FPS Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_frameRate = 60;
							refreshWindow();
						}
						break;
					case 4: // VSync ON Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_vSyncActive = true;
							m_frameRate = 0;
							refreshWindow();
						}
						break;
					case 5: // VSync OFF Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_vSyncActive = false;
							m_frameRate = 0;
							refreshWindow();
						}
						break;
					case 6: // Back Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							refreshWindow();
							m_currentSettingsPage = SettingsPage::LIST;
						}
						break;
					}
				}
			} // End Graphics Settings Page
			else if (m_currentSettingsPage == SettingsPage::AUDIO) {
				for (std::list<GUI::Button>::iterator it = btnLst_audioSettings.begin(); it != btnLst_audioSettings.end(); ++it) {
					switch (i++) {
					case 0: // Back Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_currentSettingsPage = SettingsPage::LIST;
						}
						break;
					}
				}
			} // End Audio Settings Page
			else if (m_currentSettingsPage == SettingsPage::GAMEPLAY) {
				for (std::list<GUI::Button>::iterator it = btnLst_gameplaySettings.begin(); it != btnLst_gameplaySettings.end(); ++it) {
					switch (i++) {
					case 0: // Back Button
						if (it->getState() == GUI::ButtonState::clicked) {
							buttonClick.play();
							m_currentSettingsPage = SettingsPage::LIST;
						}
						break;
					}
				}
			} // End Gameplay Settings Page
		} // End Button Handling
	} // End Settings controls

	// Handle the Game Over controls
	else if (m_gameState == GameState::GAME_OVER) {
		// Begin Button handling
		if (evnt.type == sf::Event::MouseButtonPressed) {
			int i = 0;
			for (std::list<GUI::Button>::iterator it = btnLst_gameOver.begin(); it != btnLst_gameOver.end(); ++it) {
				switch (i++) {
				case 0: // Retry Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						m_gameState = GameState::LEVELING_UP;
						wave = 0;
						score = 0;

						// Reset the player's stats
						m_Player.resetPlayerStats();
					}
					break;
				case 1: // Main Menu Button
					if (it->getState() == GUI::ButtonState::clicked) {
						buttonClick.play();
						m_gameState = GameState::MAIN_MENU;
					}
					break;
				}
			}
		} // End Button Handling
	} // End Game Over controls
}