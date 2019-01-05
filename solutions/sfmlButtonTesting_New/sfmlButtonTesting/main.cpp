/**
*	@author			[NAME]
*	@creationDate	XXXX/XX/XX	YYYY/MM/DD
*	@description	
*/

#include "Button.h"

int main() {
	/***-----------------***\
	| Setting up Game Files |
	\***-----------------***/

	sf::Vector2f resolution;
	/*resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;*/
	resolution.x = 800;
	resolution.y = 600;

	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y),
		"SFML Main Window", sf::Style::Default);

	// Create a an SFML View
	sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	
	sf::Font myfont;
	if (!myfont.loadFromFile("fonts/contb.ttf")) {//http://www.dafont.com/continuum.font
		std::cerr << "Could not find contb.ttf font." << std::endl;
	}

	GUI::Button yeah("Yeah!", myfont, sf::Vector2f(100.f, 100.f), GUI::Style::save);
	GUI::Button nope("Nope", myfont, sf::Vector2f(100.f, 200.f), GUI::Style::cancel);
	GUI::Button nice("Nice...", myfont, sf::Vector2f(300.f, 100.f), GUI::Style::clean);
	GUI::Button custom("Sweet", myfont, sf::Vector2f(300.f, 200.f), GUI::Style::none);
	custom.setBorderThickness(2.f);
	custom.setBorderRadius(20.f);
	custom.setBorderColour(sf::Color(255, 255, 255, 255));
	custom.setColourNormal(sf::Color(200, 0, 200, 255));
	custom.setColourHover(sf::Color(255, 0, 255, 100));
	custom.setColourClicked(sf::Color(150, 0, 150, 255));
	custom.setColourTextNormal(sf::Color(255, 255, 255, 255));
	custom.setColourTextHover(sf::Color(255, 255, 0, 255));
	custom.setColourTextClicked(sf::Color(255, 0, 0, 255));

	/***--------------***\
	| The Main Game Loop |
	\***--------------***/

	while (window.isOpen()) {
		/***--------***\
		| Handle Input |
		\***--------***/

		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
				return(0);
			}
		}

		/***------------***\
		| Update the Frame |
		\***------------***/

		yeah.update(e, window);
		nope.update(e, window);
		nice.update(e, window);
		custom.update(e, window);

		/***----------***\
		| Draw the Frame |
		\***----------***/

		window.clear();

		window.draw(yeah);
		window.draw(nope);
		window.draw(nice);
		window.draw(custom);

		window.display();
	}

	return(0);
}