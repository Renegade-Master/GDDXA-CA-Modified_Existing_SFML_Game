/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::initButtons() {
	// Game Over Buttons
	gameOverButtons.push_back(GUI::Button("Retry", font, sf::Vector2f(resolution.x * 0.3, resolution.y * 0.95), GUI::Style::none));
	gameOverButtons.push_back(GUI::Button("Main Menu", font, sf::Vector2f(resolution.x * 0.6, resolution.y * 0.95), GUI::Style::cancel));

	// Level Up Buttons
	levelUpButtons.push_back(GUI::Button("Rate of Fire ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.3), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Clip Size ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.4), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Health ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Run Speed ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Health Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Ammo Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.8), GUI::Style::none));
	levelUpButtons.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95), GUI::Style::cancel));

	// Main Menu Buttons
	mainMenuButtons.push_back(GUI::Button("Play", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.5), GUI::Style::clean));
	mainMenuButtons.push_back(GUI::Button("Settings", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.6), GUI::Style::none));
	mainMenuButtons.push_back(GUI::Button("Quit", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.7), GUI::Style::cancel));

	// Settings Buttons
	settingsButtons.push_back(GUI::Button("Graphics Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Gameplay Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Audio Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::Style::none));
	settingsButtons.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.9), GUI::Style::cancel));
}