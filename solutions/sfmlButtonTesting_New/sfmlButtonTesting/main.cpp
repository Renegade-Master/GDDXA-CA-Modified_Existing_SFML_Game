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

	GUI::Button btn_01("Don't", myfont, sf::Vector2f(100.f, 100.f), GUI::Style::save);
	GUI::Button btn_02("The", myfont, sf::Vector2f(100.f, 200.f), GUI::Style::cancel);
	GUI::Button btn_03("Press", myfont, sf::Vector2f(300.f, 100.f), GUI::Style::clean);
	GUI::Button btn_04("Buttons", myfont, sf::Vector2f(300.f, 200.f), GUI::Style::none);
	btn_04.setBorderThickness(2.f);
	btn_04.setBorderRadius(20.f);
	btn_04.setBorderColour(sf::Color(255, 255, 255, 255));
	btn_04.setColourNormal(sf::Color(200, 0, 200, 255));
	btn_04.setColourHover(sf::Color(255, 0, 255, 100));
	btn_04.setColourClicked(sf::Color(150, 0, 150, 255));
	btn_04.setColourTextNormal(sf::Color(255, 255, 255, 255));
	btn_04.setColourTextHover(sf::Color(255, 255, 0, 255));
	btn_04.setColourTextClicked(sf::Color(255, 0, 0, 255));

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

		btn_01.update(e, window);
		btn_02.update(e, window);
		btn_03.update(e, window);
		btn_04.update(e, window);

		/***----------***\
		| Draw the Frame |
		\***----------***/

		window.clear();

		window.draw(btn_01);
		window.draw(btn_02);
		window.draw(btn_03);
		window.draw(btn_04);

		window.display();
	}

	return(0);
}