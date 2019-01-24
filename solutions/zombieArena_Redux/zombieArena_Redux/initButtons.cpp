/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/24	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

void DevilSpawn::initButtons() {
	// Delete any old buttons
	/*if (btnLst_mainMenu.size() != 0) { btnLst_mainMenu.clear(); }
	if (btnLst_levelUp.size() != 0) { btnLst_levelUp.clear(); }
	if (btnLst_gameOver.size() != 0) { btnLst_gameOver.clear(); }
	if (btnLst_allSettings.size() != 0) { btnLst_allSettings.clear(); }
	if (btnLst_graphicsSettings.size() != 0) { btnLst_graphicsSettings.clear(); }
	if (btnLst_audioSettings.size() != 0) { btnLst_audioSettings.clear(); }
	if (btnLst_gameplaySettings.size() != 0) { btnLst_gameplaySettings.clear(); }*/

	// Main Menu Buttons
	btnLst_mainMenu.push_back(GUI::Button("Play", font, sf::Vector2f(resolution.x * 0.25f, resolution.y * 0.5f), GUI::ButtonStyle::clean));
	btnLst_mainMenu.push_back(GUI::Button("Settings", font, sf::Vector2f(resolution.x * 0.25f, resolution.y * 0.6f), GUI::ButtonStyle::none));
	btnLst_mainMenu.push_back(GUI::Button("Quit", font, sf::Vector2f(resolution.x * 0.25f, resolution.y * 0.7f), GUI::ButtonStyle::cancel));

	// Game Over Buttons
	btnLst_gameOver.push_back(GUI::Button("Retry", font, sf::Vector2f(resolution.x * 0.3f, resolution.y * 0.95f), GUI::ButtonStyle::none));
	btnLst_gameOver.push_back(GUI::Button("Main Menu", font, sf::Vector2f(resolution.x * 0.6f, resolution.y * 0.95f), GUI::ButtonStyle::cancel));

	// Level Up Buttons
	btnLst_levelUp.push_back(GUI::Button("Rate of Fire ++", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.3f), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Clip Size ++", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.4f), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Health ++", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.5f), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Run Speed ++", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.6f), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Health Pickup ++", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.7f), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Ammo Pickup ++", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.8f), GUI::ButtonStyle::none));
	btnLst_levelUp.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.95f), GUI::ButtonStyle::cancel));
	
	// Settings Buttons
	btnLst_allSettings.push_back(GUI::Button("Graphics Settings", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.5f), GUI::ButtonStyle::none));
	btnLst_allSettings.push_back(GUI::Button("Gameplay Settings", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.6f), GUI::ButtonStyle::none));
	btnLst_allSettings.push_back(GUI::Button("Audio Settings", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.7f), GUI::ButtonStyle::none));
	btnLst_allSettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.9f), GUI::ButtonStyle::cancel));

	// Settings - Graphics Buttons
	btnLst_graphicsSettings.push_back(GUI::Button("Fullscreen", font, sf::Vector2f(resolution.x * 0.40, resolution.y * 0.32f), GUI::ButtonStyle::none));
	btnLst_graphicsSettings.push_back(GUI::Button("Windowed", font, sf::Vector2f(resolution.x * 0.66, resolution.y * 0.32f), GUI::ButtonStyle::none));
	btnLst_graphicsSettings.push_back(GUI::Button("30 FPS", font, sf::Vector2f(resolution.x * 0.40, resolution.y * 0.43f), GUI::ButtonStyle::none));
	btnLst_graphicsSettings.push_back(GUI::Button("60 FPS", font, sf::Vector2f(resolution.x * 0.66, resolution.y * 0.43f), GUI::ButtonStyle::none));
	btnLst_graphicsSettings.push_back(GUI::Button("ON", font, sf::Vector2f(resolution.x * 0.40, resolution.y * 0.54f), GUI::ButtonStyle::none));
	btnLst_graphicsSettings.push_back(GUI::Button("OFF", font, sf::Vector2f(resolution.x * 0.66, resolution.y * 0.54f), GUI::ButtonStyle::none));
	btnLst_graphicsSettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.9f), GUI::ButtonStyle::cancel));

	// Settings - Audio Buttons
	btnLst_audioSettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.9f), GUI::ButtonStyle::cancel));

	// Settings - Gameplay Buttons
	btnLst_gameplaySettings.push_back(GUI::Button("Back", font, sf::Vector2f(resolution.x * 0.8f, resolution.y * 0.9f), GUI::ButtonStyle::cancel));
}