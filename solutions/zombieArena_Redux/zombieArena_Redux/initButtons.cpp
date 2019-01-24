/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::initButtons() {
	// Game Over Buttons
	btnLst_gameOver.push_back(GUI::Button("Retry", font, sf::Vector2f(resolution.x * 0.3, resolution.y * 0.95), GUI::ButtonStyle::none));
	btnLst_gameOver.push_back(GUI::Button("Main Menu", font, sf::Vector2f(resolution.x * 0.6, resolution.y * 0.95), GUI::ButtonStyle::cancel));

	// Level Up Buttons
	btnLst_levelUp.push_back(GUI::Button("Rate of Fire ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.3), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Clip Size ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.4), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Health ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Run Speed ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Health Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Ammo Pickup ++", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.8), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.95), GUI::ButtonStyle::cancel));

	// Main Menu Buttons
	btnLst_mainMenu.push_back(GUI::Button("Play", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.5), GUI::ButtonStyle::clean));
	btnLst_mainMenu.push_back(GUI::Button("Settings", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.6), GUI::ButtonStyle::none));
	btnLst_mainMenu.push_back(GUI::Button("Quit", font, sf::Vector2f(resolution.x * 0.25, resolution.y * 0.7), GUI::ButtonStyle::cancel));

	// Settings Buttons
	btnLst_allSettings.push_back(GUI::Button("Graphics Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.5), GUI::ButtonStyle::none));
	btnLst_allSettings.push_back(GUI::Button("Gameplay Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.6), GUI::ButtonStyle::none));
	btnLst_allSettings.push_back(GUI::Button("Audio Settings", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.7), GUI::ButtonStyle::none));
	btnLst_allSettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.9), GUI::ButtonStyle::cancel));

	// Settings - Graphics Buttons
	btnLst_graphicsSettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.2, resolution.y * 0.9), GUI::ButtonStyle::cancel));

	// Settings - Audio Buttons
	btnLst_audioSettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5, resolution.y * 0.9), GUI::ButtonStyle::cancel));

	// Settings - Gameplay Buttons
	btnLst_gameplaySettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.8, resolution.y * 0.9), GUI::ButtonStyle::cancel));
}