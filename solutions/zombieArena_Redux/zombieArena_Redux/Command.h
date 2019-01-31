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
	virtual void execute(Player& pc) = 0;
};

/*
*	Command supplied as Default when controller input is NULL
*/
class cmd_Null : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Direction = Player::Direction::IDLE;
	}
};

/**
*	Set the Character to run Up
*/
class cmd_RunUp : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Direction = Player::Direction::UP;
	}
};

/**
*	Set the Character to run Left
*/
class cmd_RunLeft : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Direction = Player::Direction::LEFT;
	}
};

/**
*	Set the Character to run Down
*/
class cmd_RunDown : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Direction = Player::Direction::DOWN;
	}
};

/**
*	Set the Character to run Right
*/
class cmd_RunRight : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Direction = Player::Direction::RIGHT;
	}
};

/**
*	Set the Character to Attacking
*/
class cmd_Shoot : public Command {
public:
	virtual void execute(Player& pc) override {
		pc.m_Action = Player::Action::ATTACKING;
	}
};

#endif // !COMMAND_H