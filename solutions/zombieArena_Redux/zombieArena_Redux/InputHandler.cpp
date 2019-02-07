/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description
*/

#include "InputHandler.h"

/**
*	Default Constructor
*/
InputHandler::InputHandler() {
	chooseScheme(ControlScheme::DEFAULT);
}

/**
*	Paramaterised Constructor
*/
void InputHandler::chooseScheme(sf::Uint32 scheme) {
	//	Keyboard Keys we want to use
	key_W = new cmd_RunUp();
	key_A = new cmd_RunLeft();
	key_S = new cmd_RunDown();;
	key_D = new cmd_RunRight();
	key_R = new cmd_Reload();
	key_SPACE = nullptr;
	key_RETURN = nullptr;
	key_BCKSPACE = nullptr;
	key_ESCAPE = nullptr;

	//	Mouse Buttons we want to use
	mouse_LMB = new cmd_Attack();
	mouse_RMB = new cmd_Reload();
	mouse_MMB = nullptr;


	if (scheme == ControlScheme::DEFAULT) {
		//	Gamepad Buttons we want to use
		cont_CROSS = nullptr;
		cont_CIRCLE = new cmd_Reload();
		cont_SQUARE = new cmd_Attack();
		cont_TRIANGLE = nullptr;

		cont_L1 = nullptr;
		cont_L2 = nullptr;
		cont_R1 = nullptr;
		cont_R2 = nullptr;

		//	Movement (Left Analog)
		cont_LEFT_STICK_LEFT = new cmd_RunLeft();
		cont_LEFT_STICK_RIGHT = new cmd_RunRight();
		cont_LEFT_STICK_UP = new cmd_RunUp();
		cont_LEFT_STICK_DOWN = new cmd_RunDown();

		//	Control Aiming (Right Analog)
		cont_RIGHT_STICK_UP = nullptr;
		cont_RIGHT_STICK_LEFT = nullptr;
		cont_RIGHT_STICK_DOWN = nullptr;
		cont_RIGHT_STICK_RIGHT = nullptr;
	}
	else if (scheme == ControlScheme::BUMPERJUMPER) {
		//	Gamepad Buttons we want to use
		cont_CROSS = nullptr;
		cont_CIRCLE = nullptr;
		cont_SQUARE = nullptr;
		cont_TRIANGLE = nullptr;

		cont_L1 = new cmd_Reload();
		cont_L2 = nullptr;
		cont_R1 = new cmd_Attack();
		cont_R2 = nullptr;

		cont_LEFT_STICK_UP = new cmd_RunUp();
		cont_LEFT_STICK_LEFT = new cmd_RunLeft();
		cont_LEFT_STICK_DOWN = new cmd_RunDown();
		cont_LEFT_STICK_RIGHT = new cmd_RunRight();

		cont_RIGHT_STICK_LEFT = nullptr;
		cont_RIGHT_STICK_RIGHT = nullptr;
		cont_RIGHT_STICK_UP = nullptr;
		cont_RIGHT_STICK_DOWN = nullptr;
	}
}

/**
*	Convert User input into Game Commands
*/
Command* InputHandler::handleInput(sf::Time t) {
	m_sinceLastInput += t;
	
	/*if (m_sinceLastInput > m_inputBlocker) {*/
		m_sinceLastInput = sf::Time::Zero;
		
		//	Keyboard Keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			return(key_W);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			return(key_A);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			return(key_S);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			return(key_D);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			return(key_R);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			return(key_SPACE);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			return(key_RETURN);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
			return(key_BCKSPACE);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return(key_ESCAPE);
		}

		//	Mouse Input
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			return(mouse_LMB);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			return(mouse_RMB);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
			return(mouse_MMB);
		}

		//	Gamepad Joysticks
		//		Left Stick
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::X) < -10.0f) {
			return(cont_LEFT_STICK_LEFT);
		}
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::X) > 10.0f) {
			return(cont_LEFT_STICK_RIGHT);
		}
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::Y) < -10.0f) {
			return(cont_LEFT_STICK_UP);
		}
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::Y) > 10.0f) {
			return(cont_LEFT_STICK_DOWN);
		}

		//		Right Stick
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::U) < -10.0f) {
			return(cont_RIGHT_STICK_LEFT);
		}
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::U) > 10.0f) {
			return(cont_RIGHT_STICK_RIGHT);
		}
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::V) < -10.0f) {
			return(cont_RIGHT_STICK_UP);
		}
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::V) > 10.0f) {
			return(cont_RIGHT_STICK_DOWN);
		}

		//	Triggers
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::Z) > 40.0f) {
			return(cont_L2);
		}
		if (sf::Joystick::getAxisPosition(1, sf::Joystick::Z) < -40.0f) {
			return(cont_R2);
		}

		//	Buttons
		if (sf::Joystick::isButtonPressed(1, 0)) {
			return(cont_CROSS);
		}
		if (sf::Joystick::isButtonPressed(1, 1)) {
			return(cont_CIRCLE);
		}
		if (sf::Joystick::isButtonPressed(1, 2)) {
			return(cont_SQUARE);
		}
		if (sf::Joystick::isButtonPressed(1, 3)) {
			return(cont_TRIANGLE);
		}
		if (sf::Joystick::isButtonPressed(1, 4)) {
			return(cont_L1);
		}
		if (sf::Joystick::isButtonPressed(1, 5)) {
			return(cont_R1);
		}
	/*}*/

	//	Nothing was pressed
	return(noInput);
}