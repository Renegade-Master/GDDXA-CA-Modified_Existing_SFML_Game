/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef DEVILSPAWN_H
#define DEVILSPAWN_H

#include <vector>
#include <fstream>
#include <list>
#include <iostream> // For Console Debugging
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"
#include "Button.h"
#include "Devil.h"
#include "DevilSpawn.h"
#include "Pickup.h"
#include "Player.h"
#include "TextureHolder.h"

class DevilSpawn {
public:
	DevilSpawn();
	void runGame();

private:
	void Input();
	void Update();
	void Draw();

	void initButtons();
	void initText();
	void initSounds();

	int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
	std::vector<Devil> createHorde(int numDevils, sf::IntRect arena);
	   
	// The game will always be in one of six states
	enum class State { PLAYING, PAUSED, MAIN_MENU, LEVELING_UP, SETTINGS, GAME_OVER };
	// Start with the MAIN_MENU state
	State state = State::MAIN_MENU;

	// Set the screen resolution and create an SFML window
	sf::Vector2f resolution;
	sf::Vector2f miniRes;

	sf::RenderWindow window;

	// Create an SFML View
	sf::View mainView;
	// Create a view for the HUD
	sf::View hudView;
	// Create a view for the MiniMap
	sf::View miniMapView;

	// Instance of TextureHolder
	TextureHolder holder;

	// Hold Events betwen frames
	sf::Event evnt;

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
	sf::Texture textureBackground;

	// Prepare a horde of Devils
	int hordeSize;
	int numHordeAlive;
	std::vector<Devil> horde = std::vector<Devil>();

	// Set a container for the Bullets
	std::vector<Bullet> bullets;

	// When was the fire button last pressed?
	sf::Time lastPressed;

	// Create a skin for the Mouse Cursor
	sf::Sprite sprite_mouse;
	sf::Texture texture_mouse;

	// Create a couple of pickups
	Pickup healthPickup;
	Pickup ammoPickup;

	// About the game
	int wave = 0;
	int score = 0;
	int hiScore = 0;

	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	sf::Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 500;

	// For the home/game over screen
	sf::Sprite spriteGameOver;
	sf::Texture textureGameOver 
		= TextureHolder::GetTexture("Graphics\\mtDoom_background.jpg");

	// Create a Sprite for the Ammo UI Icon
	sf::Sprite spriteAmmoIcon;
	sf::Texture textureAmmoIcon
		= TextureHolder::GetTexture("Graphics\\ammo_icon.png");

	// A container for the Font
	sf::Font font;

	// Declare Text containers
	sf::Text pausedText;
	sf::Text gameOverText;
	sf::Text levelUpText;
	sf::Text mainMenuText;
	sf::Text settingsText;
	sf::Text ammoText;
	sf::Text scoreText;
	sf::Text hiScoreText;
	sf::Text hordeRemainingText;
	sf::Text waveNumberText;

	// Declare Buttons Lists
	std::list<GUI::Button> gameOverButtons;
	std::list<GUI::Button> levelUpButtons;
	std::list<GUI::Button> mainMenuButtons;
	std::list<GUI::Button> settingsButtons;

	// Declare Shapes
	sf::RectangleShape pausedShader;
	sf::RectangleShape miniMapBorder;
	sf::RectangleShape healthBar;

	// Declare Sounds
	sf::SoundBuffer hitBuffer;
	sf::Sound hit;
	sf::SoundBuffer splatBuffer;
	sf::Sound splat;
	sf::SoundBuffer shootBuffer;
	sf::Sound shoot;
	sf::SoundBuffer reloadBuffer;
	sf::Sound reload;
	sf::SoundBuffer reloadFailedBuffer;
	sf::Sound reloadFailed;
	sf::SoundBuffer powerupBuffer;
	sf::Sound powerup;
	sf::SoundBuffer pickupBuffer;
	sf::Sound pickup;
	sf::SoundBuffer buttonClickBuffer;
	sf::Sound buttonClick;
};

#endif // DEVILSPAWN_H