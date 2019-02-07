/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/05	YYYY/MM/DD
*	@description	...
*/

#include "DevilTypes.h"

/**
*	Bloater Devil Class
*/
Bloater::Bloater() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\demonEnemy_01.png"));

	this->m_Speed = 40;
	this->m_Health = 5;
}

/**
*	Chaser Devil Class
*/
Chaser::Chaser() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\chaser_headless.png"));

	this->m_Speed = 70;
	this->m_Health = 1;
}

/**
*	Crawler Devil Class
*/
Crawler::Crawler() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\crawler.png"));

	this->m_Speed = 20;
	this->m_Health = 3;
}