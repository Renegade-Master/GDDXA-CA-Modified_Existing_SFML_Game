/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

int DevilSpawn::runGame() {
	/***-----------------***\
	| Setting up Game Files |
	\***-----------------***/

	// Instance of TextureHolder
	TextureHolder holder;

	/*resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;*/
	resolution.x = 1280;
	resolution.y = 720;
	miniRes.x = 256;
	miniRes.y = 256;

	window.create(sf::VideoMode(resolution.x, resolution.y),
		"Devil Spawn", sf::Style::Default);

	// Create the Main SFML View
	mainView.setSize(resolution);
	mainView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a view for the HUD
	hudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a view for the MiniMap
	miniMapView.setSize(miniRes);
	miniMapView.setViewport(sf::FloatRect(0, resolution.y - miniRes.y, miniRes.x, miniRes.y));
	//miniMapView.reset(sf::FloatRect(0, resolution.y - miniRes.y, miniRes.x, miniRes.y));

	// Clock for timings
	sf::Clock clock;
	// How long has the PLAYING state been active
	sf::Time gameTimeTotal;

	// Where is the mouse in relation to world coordinates
	sf::Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	sf::Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	sf::IntRect arena;

	// Create the background
	sf::VertexArray background;
	// Load the texture for our background vertex array
	sf::Texture textureBackground = TextureHolder::GetTexture(
		"Graphics\\background_sheet_stretch.png");

	// Prepare a horde of Devils
	int hordeSize;
	int numHordeAlive;
	std::vector<Devil> horde = std::vector<Devil>();

	// Set fixed amount of bullets
	std::vector<Bullet> bullets(100);
	
	// When was the fire button last pressed?
	sf::Time lastPressed;

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	sf::Sprite sprite_mouse;
	sf::Texture texture_mouse;
	sprite_mouse.setOrigin(25, 25);
	//sprite_mouse.setOrigin(texture_mouse.getSize().x / 2, texture_mouse.getSize().y / 2);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// About the game
	int score = 0;
	int hiScore = 0;

	// For the home/game over screen
	sf::Sprite spriteGameOver;
	sf::Texture textureGameOver = TextureHolder::GetTexture("Graphics\\mtDoom_background.jpg");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Create a sprite for the ammo icon
	sf::Sprite spriteAmmoIcon;
	sf::Texture textureAmmoIcon = TextureHolder::GetTexture("Graphics\\ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, resolution.y - 60);

	// Load the font
	sf::Font font;
	font.loadFromFile("Fonts\\firstordersemital.ttf");

	// Paused
	sf::Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(85);
	pausedText.setFillColor(sf::Color::White);
	pausedText.setPosition(resolution.x * 0.075, resolution.y * 0.25);
	pausedText.setString("Press Enter to continue or\nQ to go to the Main Menu");
	
	sf::RectangleShape pausedShader;
	pausedShader.setSize(sf::Vector2f(resolution.x, resolution.y));
	pausedShader.setPosition(0.0, 0.0);
	pausedShader.setFillColor(sf::Color(sf::Color::Black));

	// Game Over
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(resolution.x / 6, resolution.y / 3);
	gameOverText.setString("You DIED!\nYour Score was: " + score);

	std::list<GUI::Button> gameOverButtons;
	gameOverButtons.push_back(GUI::Button("Retry", font, sf::Vector2f(resolution.x * 0.3, resolution.y * 0.95), GUI::Style::none));
	gameOverButtons.push_back(GUI::Button("Main Menu", font, sf::Vector2f(resolution.x * 0.6, resolution.y * 0.95), GUI::Style::cancel));

	// Levelling up
	sf::Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(70);
	levelUpText.setFillColor(sf::Color::White);
	levelUpText.setPosition(50, 30);
	std::stringstream levelUpStream;
	levelUpStream << "Please choose an Upgrade" << std::endl;
	levelUpText.setString(levelUpStream.str());

	std::list<GUI::Button> levelUpButtons;
	levelUpButtons.push_back(GUI::Button("Rate of Fire ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.3), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Clip Size ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.4), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Health ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Run Speed ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Health Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Ammo Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.8), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95), GUI::Style::cancel));

	// Main Menu
	sf::Text mainMenuText;
	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(70);
	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setPosition(50, 100);
	std::stringstream mainMenuStream;
	mainMenuStream	<< "Welcome to DEVILSPAWN" << std::endl;
	mainMenuText.setString(mainMenuStream.str());

	std::list<GUI::Button> mainMenuButtons;
	mainMenuButtons.push_back(GUI::Button("Play", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.5), GUI::Style::clean));
	mainMenuButtons.push_back(GUI::Button("Settings", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.6), GUI::Style::none));
	mainMenuButtons.push_back(GUI::Button("Quit", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.7), GUI::Style::cancel));

	// Settings
	sf::Text settingsText;
	settingsText.setFont(font);
	settingsText.setCharacterSize(70);
	settingsText.setFillColor(sf::Color::White);
	settingsText.setPosition(50, 100);
	std::stringstream settingsStream;
	settingsStream << "Configure Game Settings" << std::endl;
	settingsText.setString(settingsStream.str());

	std::list<GUI::Button> settingsButtons;
	settingsButtons.push_back(GUI::Button("Graphics Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Gameplay Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Audio Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.9), GUI::Style::cancel));

	//MiniMap Border
	sf::RectangleShape miniMapBorder;
	miniMapBorder.setSize(sf::Vector2f(resolution.x, resolution.y));
	miniMapBorder.setOutlineThickness(10.0);
	miniMapBorder.setOutlineColor(sf::Color(sf::Color::Black));

	// Ammo
	sf::Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setPosition(75, resolution.y - 60);

	// Score
	sf::Text scoreText;
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
	sf::Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color::White);
	hiScoreText.setPosition(resolution.x - 300, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// Zombies remaining
	sf::Text hordeRemainingText;
	hordeRemainingText.setFont(font);
	hordeRemainingText.setCharacterSize(55);
	hordeRemainingText.setFillColor(sf::Color::White);
	hordeRemainingText.setPosition(resolution.x - 350, resolution.y - 60);
	hordeRemainingText.setString("Horde Size: 0");

	// Wave number
	int wave = 0;
	sf::Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(sf::Color::White);
	waveNumberText.setPosition(resolution.x - 275, resolution.y - 120);
	waveNumberText.setString("Wave: 0");

	// Health bar
	sf::RectangleShape healthBar;
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setPosition(resolution.x / 2, resolution.y - 60);
		
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	sf::Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 500;

	// Prepare the hit sound
	sf::SoundBuffer hitBuffer;
	//splatBuffer.loadFromFile("Audio\\hit.wav");
	hitBuffer.loadFromFile("Audio\\IMPACT_Generic_09_Short_mono.wav");
	sf::Sound hit;
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	sf::SoundBuffer splatBuffer;
	//splatBuffer.loadFromFile("Audio\\splat.wav");
	splatBuffer.loadFromFile("Audio\\GORE_Splat_Hit_Short_mono.wav");
	sf::Sound splat;
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	sf::SoundBuffer shootBuffer;
	//splatBuffer.loadFromFile("Audio\\shoot.wav");
	shootBuffer.loadFromFile("Audio\\FIREARM_Handgun_B_FS92_9mm_Fire_Short_Reverb_Tail_RR2_stereo.wav");
	sf::Sound shoot;
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	sf::SoundBuffer reloadBuffer;
	//reloadBuffer.loadFromFile("Audio\\reload.wav");
	reloadBuffer.loadFromFile("Audio\\RELOAD_Clicks_Double_mono.wav");
	sf::Sound reload;
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	sf::SoundBuffer reloadFailedBuffer;
	//reloadFailedBuffer.loadFromFile("Audio\\reload_failed.wav");
	reloadFailedBuffer.loadFromFile("Audio\\RELOAD_Dry_Fire_stereo.wav");
	sf::Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	// Prepare the powerup sound
	sf::SoundBuffer powerupBuffer;
	//powerupBuffer.loadFromFile("Audio\\powerup.wav");
	powerupBuffer.loadFromFile("Audio\\CHARGE_Sci-Fi_High_Pass_Sweep_12_Semi_Up_500ms_stereo.wav");
	sf::Sound powerup;
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	sf::SoundBuffer pickupBuffer;
	//pickupBuffer.loadFromFile("Audio\\pickup.wav");
	pickupBuffer.loadFromFile("Audio\\8BIT_RETRO_Coin_Collect_Two_Note_Deep_Twinkle_mono.wav");
	sf::Sound pickup;
	pickup.setBuffer(pickupBuffer);

	// Prepare the button sound
	sf::SoundBuffer buttonClickBuffer;
	buttonClickBuffer.loadFromFile("Audio\\UI_Click_Organic_49_Dry_Mono.wav");
	sf::Sound buttonClick;
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
					> 1000 / player.fireRate && player.bulletsInClip > 0)	{

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
	}// End game loop

	return(0);
}