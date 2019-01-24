/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::initText() {
	// Paused
	pausedText.setFont(font);
	pausedText.setCharacterSize(85);
	pausedText.setFillColor(sf::Color::White);
	pausedText.setPosition(resolution.x * 0.075, resolution.y * 0.25);
	pausedText.setString("Press Enter to continue or\nQ to go to the Main Menu");
	
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
	std::stringstream levelUpStream;
	levelUpStream << "Please choose an Upgrade" << std::endl;
	levelUpText.setString(levelUpStream.str());

	// Main Menu
	mainMenuText.setFont(font);
	mainMenuText.setCharacterSize(70);
	mainMenuText.setFillColor(sf::Color::White);
	mainMenuText.setPosition(50, 100);
	std::stringstream mainMenuStream;
	mainMenuStream << "Welcome to DEVILSPAWN" << std::endl;
	mainMenuText.setString(mainMenuStream.str());

	// Settings
	settingsText.setFont(font);
	settingsText.setCharacterSize(70);
	settingsText.setFillColor(sf::Color::White);
	settingsText.setPosition(50, 100);
	std::stringstream settingsStream;
	settingsStream << "Configure Game Settings" << std::endl;
	settingsText.setString(settingsStream.str());

	// Ammo
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(sf::Color::White);
	ammoText.setPosition(75, resolution.y - 60);

	// Score and Hi-Score
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(20, 0);
	
	// Load the high score from a text file
	std::ifstream inputFile("gamedata\\scores.txt");
	if (inputFile.is_open()) {
		inputFile >> hiScore;
		inputFile.close();
	}

	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(sf::Color::White);
	hiScoreText.setPosition(resolution.x - 300, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// Zombies Remaining
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
}