/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

int main() {
	/***-----------------***\
	| Setting up Game Files |
	\***-----------------***/

	// Instance of TextureHolder
	TextureHolder holder;

	// The game will always be in one of five states
	enum class State { PAUSED, MAIN_MENU, LEVELING_UP, GAME_OVER, PLAYING };
	// Start with the GAME_OVER state
	State state = State::MAIN_MENU;

	// Set the screen resolution and create an SFML window
	sf::Vector2f resolution;
	sf::Vector2f miniRes;
	/*resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;*/
	resolution.x = 1280;
	resolution.y = 720;
	miniRes.x = 256;
	miniRes.y = 256;

	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y),
		"Devil Spawm", sf::Style::Default);

	// Create an SFML View
	sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// Create a view for the HUD
	sf::View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));	
	// Create a view for the MiniMap
	sf::View miniMapView(sf::FloatRect(0, resolution.y - miniRes.y, miniRes.x, miniRes.y));

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
		"Graphics/background_sheet_stretch.png");

	// Prepare a horde of Devils
	int hordeSize;
	int numHordeAlive;
	Devil* horde = NULL;

	// Set fixed amount of bullets
	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	// When was the fire button last pressed?
	sf::Time lastPressed;

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	sf::Sprite sprite_mouse;
	sf::Texture texture_mouse;
	sprite_mouse.setOrigin(25, 25);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// About the game
	int score = 0;
	int hiScore = 0;

	// For the home/game over screen
	sf::Sprite spriteGameOver;
	sf::Texture textureGameOver = TextureHolder::GetTexture("Graphics/mtDoom_background.jpg");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Create a sprite for the ammo icon
	sf::Sprite spriteAmmoIcon;
	sf::Texture textureAmmoIcon = TextureHolder::GetTexture("Graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, resolution.y - 60);

	// Load the font
	sf::Font font;
	font.loadFromFile("Fonts/firstordersemital.ttf");

	// Paused
	sf::Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(sf::Color::White);
	pausedText.setPosition(resolution.x / 7, resolution.y / 4);
	pausedText.setString("Press Enter to continue or\nQ to go to the Main Menu");

	// Game Over
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(resolution.x / 6, resolution.y / 3);
	//gameOverText.setString("Press Enter to Play");
	gameOverText.setString("You DIED!\nYour Score was: " + score);

	// Levelling up
	sf::Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(70);
	levelUpText.setFillColor(sf::Color::White);
	levelUpText.setPosition(50, 100);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());

	// Main Menu
	sf::Text mainMenuText;
	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(70);
	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setPosition(50, 100);
	std::stringstream mainMenuStream;
	mainMenuStream	<< "Welcome to DevilSpawn\n" << std::endl;
					/*<< "\n1 - START GAME\n"
					<< "\n\nQ - Quit Game"
					<< std::endl;*/
	mainMenuText.setString(mainMenuStream.str());
	GUI::Button btn_mainMenu_play("Play", font, sf::Vector2f(resolution.x/4, resolution.y * 0.5), GUI::Style::clean);
	GUI::Button btn_mainMenu_settings("Settings", font, sf::Vector2f(resolution.x / 4, resolution.y * 0.6), GUI::Style::none);
	GUI::Button btn_mainMenu_quit("Quit", font, sf::Vector2f(resolution.x / 4, resolution.y * 0.7), GUI::Style::none);

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
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	// Hi Score
	sf::Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color::White);
	hiScoreText.setPosition(resolution.x - 275, 0);
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
	//splatBuffer.loadFromFile("Audio/hit.wav");
	hitBuffer.loadFromFile("Audio/IMPACT_Generic_09_Short_mono.wav");
	sf::Sound hit;
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	sf::SoundBuffer splatBuffer;
	//splatBuffer.loadFromFile("Audio/splat.wav");
	splatBuffer.loadFromFile("Audio/GORE_Splat_Hit_Short_mono.wav");
	sf::Sound splat;
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	sf::SoundBuffer shootBuffer;
	//splatBuffer.loadFromFile("Audio/shoot.wav");
	shootBuffer.loadFromFile("Audio/FIREARM_Handgun_B_FS92_9mm_Fire_Short_Reverb_Tail_RR2_stereo.wav");
	sf::Sound shoot;
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	sf::SoundBuffer reloadBuffer;
	//reloadBuffer.loadFromFile("Audio/reload.wav");
	reloadBuffer.loadFromFile("Audio/RELOAD_Clicks_Double_mono.wav");
	sf::Sound reload;
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	sf::SoundBuffer reloadFailedBuffer;
	//reloadFailedBuffer.loadFromFile("Audio/reload_failed.wav");
	reloadFailedBuffer.loadFromFile("Audio/RELOAD_Dry_Fire_stereo.wav");
	sf::Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	// Prepare the powerup sound
	sf::SoundBuffer powerupBuffer;
	//powerupBuffer.loadFromFile("Audio/powerup.wav");
	powerupBuffer.loadFromFile("Audio/CHARGE_Sci-Fi_High_Pass_Sweep_12_Semi_Up_500ms_stereo.wav");
	sf::Sound powerup;
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	sf::SoundBuffer pickupBuffer;
	//pickupBuffer.loadFromFile("Audio/pickup.wav");
	pickupBuffer.loadFromFile("Audio/8BIT_RETRO_Coin_Collect_Two_Note_Deep_Twinkle_mono.wav");
	sf::Sound pickup;
	pickup.setBuffer(pickupBuffer);

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
			if (evnt.type == sf::Event::KeyPressed) {
				// Pause a game while playing
				if (evnt.key.code == sf::Keyboard::Escape &&
					state == State::PLAYING) {
					state = State::PAUSED;
				}

				// Restart while paused
				else if (evnt.key.code == sf::Keyboard::Return &&
					state == State::PAUSED)	{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Handle the player quitting
				else if (evnt.key.code == sf::Keyboard::Q &&
					state == State::PAUSED) {
					state = State::MAIN_MENU;
				}
				
				// Spin and zoom the world				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	{
					mainView.rotate(.5f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					mainView.rotate(-.5f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					mainView.zoom(.99f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))	{
					mainView.zoom(1.01f);
				}
				// End spinning and zooming

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
							// Only few bullets left
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;				
							reload.play();
						}
						else {
							// More here soon?!
							reloadFailed.play();
						}
					}
				}
			}
		}// End event polling

		// Handle the main menu state
		if (state == State::MAIN_MENU) {
			//std::cout << "Entered the Main Menu." << std::endl;

			btn_mainMenu_play.update(evnt, window);
			btn_mainMenu_settings.update(evnt, window);
			btn_mainMenu_quit.update(evnt, window);

			switch (evnt.key.code) {
			case sf::Keyboard::Num1:
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
				break;
			case sf::Keyboard::Z:
				window.close();
				break;
			default:
				break;
			}
		}

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
					bullets[currentBullet].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99) {
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					shoot.play();
					bulletsInClip--;
				}
			}// End fire a bullet
		}// End WASD while playing

		// Handle the levelling up state
		if (state == State::LEVELING_UP) {
			// Handle the player levelling up
			if (evnt.key.code == sf::Keyboard::Num1) {
				// Increase fire rate
				fireRate++;
				state = State::PLAYING;
			}

			if (evnt.key.code == sf::Keyboard::Num2) {
				// Increase clip size
				clipSize += clipSize;
				state = State::PLAYING;
			}

			if (evnt.key.code == sf::Keyboard::Num3) {
				// Increase health
				player.upgradeHealth();
				state = State::PLAYING;
			}

			if (evnt.key.code == sf::Keyboard::Num4) {
				// Increase speed
				player.upgradeSpeed();
				state = State::PLAYING;
			}

			if (evnt.key.code == sf::Keyboard::Num5) {
				healthPickup.upgrade();
				state = State::PLAYING;
			}

			if (evnt.key.code == sf::Keyboard::Num6) {
				ammoPickup.upgrade();
				state = State::PLAYING;
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
				delete[] horde;
				horde = createHorde(hordeSize, arena);
				numHordeAlive = hordeSize;

				// Play the powerup sound
				powerup.play();

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		}// End levelling up

		/***------------***\
		| Update the Frame |
		\***------------***/
		
		if (state == State::PLAYING) {
			// Change the mouse to the GAME mouse
			window.setMouseCursorVisible(false);
			texture_mouse = TextureHolder::GetTexture("Graphics/crosshair.png");
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
			for (int i = 0; i < hordeSize; i++) {
				if (horde[i].isAlive()) {
					horde[i].update(dt.asSeconds(), playerPosition);
				}
			}

			// Update any bullets that are in-flight
			for (int i = 0; i < 100; i++) {
				if (bullets[i].isInFlight()) {
					bullets[i].update(dtAsSeconds);
				}
			}

			// Update the pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);

			// Collision detection
			// Have any horde been shot?
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < hordeSize; j++) {
					if (bullets[i].isInFlight() && 
						horde[j].isAlive()) {
						if (bullets[i].getPosition().intersects
							(horde[j].getPosition())) {
							// Stop the bullet
							bullets[i].stop();

							// Register the hit and see if it was a kill
							if (horde[j].hit()) {
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
			for (int i = 0; i < hordeSize; i++) {
				if (player.getPosition().intersects
					(horde[i].getPosition()) && horde[i].isAlive())	{

					if (player.hit(gameTimeTotal)) {
						// More here later
						hit.play();
					}

					if (player.getHealth() <= 0) {
						state = State::GAME_OVER;

						std::ofstream outputFile("gamedata/scores.txt");
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

		if (state == State::MAIN_MENU) {
			window.setMouseCursorVisible(true);
			//texture_mouse = TextureHolder::GetTexture("Graphics/crosshair.png");
			//sprite_mouse.setTexture(texture_mouse);
		}

		/***----------***\
		| Draw the Frame |
		\***----------***/
		
		window.clear();

		if (state == State::PLAYING) {

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);

			// Draw the horde
			for (int i = 0; i < hordeSize; i++) {
				window.draw(horde[i].getSprite());
			}

			for (int i = 0; i < 100; i++) {
				if (bullets[i].isInFlight()) {
					window.draw(bullets[i].getShape());
				}
			}

			// Draw the player
			window.draw(player.getSprite());

			// Draw the pickups is currently spawned
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

		if (state == State::LEVELING_UP) {
			window.draw(spriteGameOver);
			window.draw(levelUpText);
		}

		if (state == State::PAUSED) {
			window.draw(pausedText);
		}

		if (state == State::GAME_OVER) {
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
		}

		if (state == State::MAIN_MENU) {
			window.setView(mainView);
			window.draw(spriteGameOver);
			window.draw(mainMenuText);
			window.draw(btn_mainMenu_play);
			window.draw(btn_mainMenu_settings);
			window.draw(btn_mainMenu_quit);
		}

		window.display();
	}// End game loop

	return(0);
}