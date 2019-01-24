/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"

DevilSpawn::DevilSpawn() {
	/***-----------------***\
	| Setting up Game Files |
	\***-----------------***/

	/*resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;*/
	resolution.x = 1280;
	resolution.y = 720;
	miniRes.x = 256;
	miniRes.y = 256;

	window.create(sf::VideoMode(resolution.x, resolution.y),
		"Devil Spawn", sf::Style::Default);

	window.setFramerateLimit(m_frameRate);
	window.setVerticalSyncEnabled(m_vSyncActive);

	// Create the Main SFML View
	mainView.setSize(resolution);
	mainView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a view for the HUD
	hudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a view for the MiniMap
	miniMapView.setSize(miniRes);
	miniMapView.setViewport(sf::FloatRect(0, resolution.y - miniRes.y, miniRes.x, miniRes.y));
	//miniMapView.reset(sf::FloatRect(0, resolution.y - miniRes.y, miniRes.x, miniRes.y));

	// Load the texture for our background vertex array
	textureBackground = TextureHolder::GetTexture(
		"Graphics\\background_sheet_stretch.png");

	// Set fixed amount of bullets
	bullets = std::vector<Bullet>(100);

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	sprite_mouse.setOrigin(25, 25);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// For the home/game over screen
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Create a sprite for the ammo icon
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, resolution.y - 60);

	// Load the font
	font.loadFromFile("Fonts\\firstordersemital.ttf");

	// Initialise all Game Text
	DevilSpawn::initText();

	// Initialise all Game Buttons
	DevilSpawn::initButtons();

	// Paused Screen
	pausedShader.setSize(sf::Vector2f(resolution.x, resolution.y));
	pausedShader.setPosition(0.0, 0.0);
	pausedShader.setFillColor(sf::Color(sf::Color::Black));

	//MiniMap Border
	miniMapBorder.setSize(sf::Vector2f(resolution.x, resolution.y));
	miniMapBorder.setOutlineThickness(10.0);
	miniMapBorder.setOutlineColor(sf::Color(sf::Color::Black));

	// Health bar
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setPosition(resolution.x / 2, resolution.y - 60);

}

void DevilSpawn::runGame() {
	/***--------------***\
	| The Main Game Loop |
	\***--------------***/

	while (window.isOpen())	{		
		Input();
		Update();
		Draw();		
	} // End game loop
}