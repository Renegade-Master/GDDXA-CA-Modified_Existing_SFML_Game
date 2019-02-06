/**
*	@author			Ciaran Bent [K00221230]
*					Owen O'Dea	[K00218956]
*					Rory Ryan	[K00218864]
*	@creationDate	2019/01/27	YYYY/MM/DD
*	@description
*/

#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include "Player.h"

/**
*	Parent/Superclass
*/
class Command {
public:
	virtual ~Command() { /*delete this;*/ }
	virtual void execute(Player& pc, sf::Vector2f target, sf::Time ft) = 0;
};

/*
*	Command supplied as Default when controller input is NULL
*/
class cmd_Null : public Command {
public:
	virtual void execute(Player& pc, sf::Vector2f target, sf::Time ft) override {
		pc.m_Movement_V = PlayerCharacter::Movement_V::IDLE;
		pc.m_Movement_H = PlayerCharacter::Movement_H::IDLE;
		//std::cout << "Executing NULL Input" << std::endl;
	}
};

/**
*	Set the Character to run Up
*/
class cmd_RunUp : public Command {
public:
	virtual void execute(Player& pc, sf::Vector2f target, sf::Time ft) override {
		pc.m_Movement_V = PlayerCharacter::Movement_V::UP;
		//std::cout << "Executing RUN UP Input" << std::endl;
	}
};

/**
*	Set the Character to run Left
*/
class cmd_RunLeft : public Command {
public:
	virtual void execute(Player& pc, sf::Vector2f target, sf::Time ft) override {
		pc.m_Movement_H = PlayerCharacter::Movement_H::LEFT;
		//std::cout << "Executing RUN LEFT Input" << std::endl;
	}
};

/**
*	Set the Character to run Down
*/
class cmd_RunDown : public Command {
public:
	virtual void execute(Player& pc, sf::Vector2f target, sf::Time ft) override {
		pc.m_Movement_V = PlayerCharacter::Movement_V::DOWN;
		//std::cout << "Executing RUN DOWN Input" << std::endl;
	}
};

/**
*	Set the Character to run Right
*/
class cmd_RunRight : public Command {
public:
	virtual void execute(Player& pc, sf::Vector2f target, sf::Time ft) override {
		pc.m_Movement_H = PlayerCharacter::Movement_H::RIGHT;
		//std::cout << "Executing RUN RIGHT Input" << std::endl;
	}
};

/**
*	Set the Character to Attacking
*/
class cmd_Attack : public Command {
public:
	virtual void execute(Player& pc, sf::Vector2f target, sf::Time ft) override {
		pc.m_Action = PlayerCharacter::Action::ATTACKING;
		pc.shoot(pc.getCentre(), target, ft);
		//std::cout << "Executing ATTACK Input" << std::endl;
	}
};

#endif // !COMMAND_H