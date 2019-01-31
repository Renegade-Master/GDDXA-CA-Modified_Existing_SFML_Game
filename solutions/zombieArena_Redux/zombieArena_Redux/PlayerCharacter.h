/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/31	YYYY/MM/DD
*	@description	...
*/

#pragma once
#ifndef PLAYERCHARACTER_H

#include <SFML/Graphics.hpp>

#include "Constants.h"

class PlayerCharacter {
public:
	
protected:
	/***---------------------***\
	|	Finite State Machines	|
	\***---------------------***/

	enum class Movement { IDLE, UP, DOWN, LEFT, RIGHT };
	Movement m_Movement = Movement::IDLE;

	enum class Action { IDLE, ATTACKING };
	Action m_Action = Action::IDLE;

	/***---------***\
	|	Variables	|
	\***---------***/

	// How much health has the PC got?
	int m_Health;

	// What is the maximum health the PC can have
	int m_MaxHealth;

	// Speed in pixels per second
	float m_Speed;

	// Maximum Speed in pixels per second
	float m_MaxSpeed;

	// When was the PC last hit
	sf::Time m_LastHit;

	/***---------***\
	|	Functions	|
	\***---------***/

	// Where is the PC
	sf::FloatRect getPosition();

	// Where is the center of the PC
	sf::Vector2f getCenter();

	// Send a copy of the sprite to main
	sf::Sprite getSprite();

	// How much health has the PC currently got?
	int getHealth();

private:

};

#endif // !PLAYERCHARACTER_H