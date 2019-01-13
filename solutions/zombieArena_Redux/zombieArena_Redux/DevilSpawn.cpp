/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

int DevilSpawn::main() {
	/***-----------------***\
	| Setting up Game Files |
	\***-----------------***/

	// Set the screen resolution and create an SFML window
	/*resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;*/
	resolution.x = 1280;
	resolution.y = 720;
	miniRes.x = 256;
	miniRes.y = 256;

	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y),
		"Devil Spawn", sf::Style::Default);

	// Create an SFML View
	sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// Create a view for the HUD
	sf::View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// Create a view for the MiniMap
	sf::View miniMapView(sf::FloatRect(0, resolution.y - miniRes.y, miniRes.x, miniRes.y));

	// Prepare a horde of Devils
	horde = std::vector<Devil>();

	// Set fixed amount of bullets
	bullets = std::vector<Bullet>(100);

	// Clock for timings
	sf::Clock clock;

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	sprite_mouse.setOrigin(25, 25);
	//sprite_mouse.setOrigin(texture_mouse.getSize().x / 2, texture_mouse.getSize().y / 2);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// For the home/game over screen
	textureGameOver = TextureHolder::GetTexture("Graphics\\mtDoom_background.jpg");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Create a sprite for the ammo icon
	textureAmmoIcon = TextureHolder::GetTexture("Graphics\\ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, resolution.y - 60);

	// Load the font
	font.loadFromFile("Fonts\\firstordersemital.ttf");

	// Paused
	pausedText.setFont(font);
	pausedText.setCharacterSize(85);
	pausedText.setFillColor(sf::Color::White);
	pausedText.setPosition(resolution.x * 0.075, resolution.y * 0.25);
	pausedText.setString("Press Enter to continue or\nQ to go to the Main Menu");
	
	pausedShader.setSize(sf::Vector2f(resolution.x, resolution.y));
	pausedShader.setPosition(0.0, 0.0);
	pausedShader.setFillColor(sf::Color(0,0,0,128));

	// Game Over
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(resolution.x / 6, resolution.y / 3);
	gameOverText.setString("You DIED!\nYour Score was: " + score);

	// Levelling up
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(70);
	levelUpText.setFillColor(sf::Color::White);
	levelUpText.setPosition(50, 30);
	levelUpStream << "Please choose an Upgrade" << std::endl;
	levelUpText.setString(levelUpStream.str());

	levelUpButtons.push_back(GUI::Button("Rate of Fire ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.3), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Clip Size ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.4), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Health ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Run Speed ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Health Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Ammo Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.8), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95), GUI::Style::cancel));

	// Main Menu
	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(70);
	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setPosition(50, 100);
	mainMenuStream	<< "Welcome to DEVILSPAWN" << std::endl;
	mainMenuText.setString(mainMenuStream.str());

	mainMenuButtons.push_back(GUI::Button("Play", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.5), GUI::Style::clean));
	mainMenuButtons.push_back(GUI::Button("Settings", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.6), GUI::Style::none));
	mainMenuButtons.push_back(GUI::Button("Quit", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.7), GUI::Style::cancel));

	// Settings
	settingsText.setFont(font);
	settingsText.setCharacterSize(70);
	settingsText.setFillColor(sf::Color::White);
	settingsText.setPosition(50, 100);
	settingsStream << "Configure Game Settings" << std::endl;
	settingsText.setString(settingsStream.str());

	settingsButtons.push_back(GUI::Button("Graphics Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Gameplay Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Audio Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.9), GUI::Style::cancel));

	// Ammo
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setPosition(75, resolution.y - 60);

	// Score
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata\\scores.txt");
	if (inputFile.is_open()) {
		inputFile >> hiScore;
		inputFile.close();
	}

	// Hi Score
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color::White);
	hiScoreText.setPosition(resolution.x - 275, 0);
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// Zombies remaining
	hordeRemainingText.setFont(font);
	hordeRemainingText.setCharacterSize(55);
	hordeRemainingText.setFillColor(sf::Color::White);
	hordeRemainingText.setPosition(resolution.x - 350, resolution.y - 60);
	hordeRemainingText.setString("Horde Size: 0");

	// Wave number
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(sf::Color::White);
	waveNumberText.setPosition(resolution.x - 275, resolution.y - 120);
	waveNumberText.setString("Wave: 0");

	// Health bar
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setPosition(resolution.x / 2, resolution.y - 60);

	// Prepare the hit sound
	hitBuffer.loadFromFile("Audio\\IMPACT_Generic_09_Short_mono.wav");
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	splatBuffer.loadFromFile("Audio\\GORE_Splat_Hit_Short_mono.wav");
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	shootBuffer.loadFromFile("Audio\\FIREARM_Handgun_B_FS92_9mm_Fire_Short_Reverb_Tail_RR2_stereo.wav");
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	reloadBuffer.loadFromFile("Audio\\RELOAD_Clicks_Double_mono.wav");
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	reloadFailedBuffer.loadFromFile("Audio\\RELOAD_Dry_Fire_stereo.wav");
	reloadFailed.setBuffer(reloadFailedBuffer);

	// Prepare the powerup sound
	powerupBuffer.loadFromFile("Audio\\CHARGE_Sci-Fi_High_Pass_Sweep_12_Semi_Up_500ms_stereo.wav");
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	pickupBuffer.loadFromFile("Audio\\8BIT_RETRO_Coin_Collect_Two_Note_Deep_Twinkle_mono.wav");
	pickup.setBuffer(pickupBuffer);

	// Prepare the button sound
	buttonClickBuffer.loadFromFile("Audio\\UI_Click_Organic_49_Dry_Mono.wav");
	buttonClick.setBuffer(buttonClickBuffer);

	/***--------------***\
	| The Main Game Loop |
	\***--------------***/

	while (window.isOpen())	{
		/***--------***\
		| Handle Input |
		\***--------***/

		// Handle events
		sf::Event evnt;
		while (window.pollEvent(evnt))	{
			// Handle Keyboard Events
			if (evnt.type == sf::Event::KeyPressed) {
				// Pause while Playing
				if (evnt.key.code == sf::Keyboard::Escape &&
					state == State::PLAYING) {
					state = State::PAUSED;
				}

				// Restart while Paused
				else if (evnt.key.code == sf::Keyboard::Return &&
					state == State::PAUSED)	{
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	{
					mainView.rotate(1.0f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					mainView.rotate(-1.0f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					mainView.zoom(.9f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	{
					mainView.zoom(1.1f);
				}
				// End spinning and zooming

				// Handle Events in PLAYING state
				if (state == State::PLAYING) {
					// Reloading
					if (evnt.key.code == sf::Keyboard::R) {
						if (bulletsSpare >= clipSize) {
							// Plenty of bullets. Reload.
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;
							reload.play();
						}
						else if (bulletsSpare > 0) {
							// Less than a clip remaining
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;
							reload.play();
						}
						else {
							// NO AMMO!!
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
					> 1000 / fireRate && bulletsInClip > 0)	{

					// Pass the centre of the player and the centre of the crosshair
					// to the shoot function
					bullets[currentBullet++].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);
					if (currentBullet > 99) {
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					shoot.play();
					bulletsInClip--;
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

							// Prepare the gun and ammo for next game
							currentBullet = 0;
							bulletsSpare = 24;
							bulletsInClip = 6;
							clipSize = 6;
							fireRate = 1;

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
							fireRate++;
							state = State::PLAYING;
						}
						break;
					case 1: // Clip Size Upgrade Button
						if (it->getState() == GUI::State::clicked) {
							buttonClick.play();// Increase clip size
							clipSize += clipSize;
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

		} // End Game Over controls

		/***------------***\
		| Update the Frame |
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
			player.update(dtAsSeconds, mouseScreenPosition);

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
					(it->getPosition()) && it->isAlive())	{

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
				bulletsSpare += ammoPickup.gotIt();
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
				ssAmmo << bulletsInClip << "/" << bulletsSpare;
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
		}

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
		}

		window.display();
	}// End game loop

	return(0);
}