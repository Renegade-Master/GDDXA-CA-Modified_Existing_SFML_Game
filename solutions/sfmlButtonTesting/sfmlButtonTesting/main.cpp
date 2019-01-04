/**
*	@author			[NAME]
*	@creationDate	XXXX/XX/XX	YYYY/MM/DD
*	@description	
*/

#include <SFML\Graphics.hpp>
#include "Button.h"

int main() {
	/***-----------------***\
	| Setting up Game Files |
	\***-----------------***/

	sf::Vector2f resolution;
	/*resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;*/
	resolution.x = 1280;
	resolution.y = 720;

	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y),
		"SFML Main Window", sf::Style::Default);

	// Create a an SFML View
	sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));



	/***--------------***\
	| The Main Game Loop |
	\***--------------***/

	while (window.isOpen()) {
		/***--------***\
		| Handle Input |
		\***--------***/

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {

			}
		}

		/***------------***\
		| Update the Frame |
		\***------------***/



		/***----------***\
		| Draw the Frame |
		\***----------***/

		window.clear();

		window.display();
	}

	return(0);
}