/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/08	YYYY/MM/DD
*	@description	Observer Pattern Implementation
*/

#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H

#include "SFML/Audio.hpp"

class Observer abstract{
public:
	//~Observer();
	virtual void onNotify() {};
};

#endif // !OBSERVER_H
