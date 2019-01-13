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
	int main();

private:
	int createBackground(sf::VertexArray& rVA, sf::IntRect arena);
	std::vector<Devil> createHorde(int numDevils, sf::IntRect arena);

	// Instance of TextureHolder
	TextureHolder holder;

	// The game will always be in one of six states
	enum class State { PLAYING, PAUSED, MAIN_MENU, LEVELING_UP, SETTINGS, GAME_OVER };
	// Start with the MAIN_MENU state
	State state = State::MAIN_MENU;

	// Set the screen resolution and create an SFML window
	sf::Vector2f resolution;
	sf::Vector2f miniRes;

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
	std::vector<Devil> horde;

	// Set fixed amount of bullets
	std::vector<Bullet> bullets;
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;
	// When was the fire button last pressed?
	sf::Time lastPressed;

	// Create a Sprite for the mouse
	sf::Sprite sprite_mouse;
	sf::Texture texture_mouse;

	// About the game
	int score = 0;
	int hiScore = 0;

	// For the home/game over screen
	sf::Sprite spriteGameOver;
	sf::Texture textureGameOver;

	// Create a sprite for the ammo icon
	sf::Sprite spriteAmmoIcon;
	sf::Texture textureAmmoIcon;

	// Load the font
	sf::Font font;

	// Paused
	sf::Text pausedText;

	sf::RectangleShape pausedShader;

	// Game Over
	sf::Text gameOverText;

	// Levelling up
	sf::Text levelUpText;
	std::stringstream levelUpStream;

	std::list<GUI::Button> levelUpButtons;

	// Main Menu
	sf::Text mainMenuText;
	std::stringstream mainMenuStream;

	std::list<GUI::Button> mainMenuButtons;

	// Settings
	sf::Text settingsText;
	std::stringstream settingsStream;

	std::list<GUI::Button> settingsButtons;

	// Ammo
	sf::Text ammoText;

	// Score
	sf::Text scoreText;

	// Hi Score
	sf::Text hiScoreText;
	std::stringstream s;

	// Zombies remaining
	sf::Text hordeRemainingText;

	// Wave number
	int wave = 0;
	sf::Text waveNumberText;

	// Health bar
	sf::RectangleShape healthBar;

	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	sf::Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 500;

	// Prepare the hit sound
	sf::SoundBuffer hitBuffer;
	sf::Sound hit;

	// Prepare the splat sound
	sf::SoundBuffer splatBuffer;
	sf::Sound splat;

	// Prepare the shoot sound
	sf::SoundBuffer shootBuffer;
	sf::Sound shoot;

	// Prepare the reload sound
	sf::SoundBuffer reloadBuffer;
	sf::Sound reload;

	// Prepare the failed sound
	sf::SoundBuffer reloadFailedBuffer;
	sf::Sound reloadFailed;

	// Prepare the powerup sound
	sf::SoundBuffer powerupBuffer;
	sf::Sound powerup;

	// Prepare the pickup sound
	sf::SoundBuffer pickupBuffer;
	sf::Sound pickup;

	// Prepare the button sound
	sf::SoundBuffer buttonClickBuffer;
	sf::Sound buttonClick;
};


#endif // DEVILSPAWN_H