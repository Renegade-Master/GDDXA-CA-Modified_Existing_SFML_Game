/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/02/05	YYYY/MM/DD
*	@description	...
*/

#include "DevilTypes.h"

/**
*	Demon Devil Class
*/
Demon::Demon() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\demonEnemy_01.png"));

	this->m_Speed = DEMON_SPEED;
	this->m_Health = DEMON_HEALTH;
}

/**
*	Chaser Devil Class
*/
Chaser::Chaser() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\chaser_headless.png"));

	this->m_Speed = CHASER_SPEED;
	this->m_Health = CHASER_HEALTH;
}

/**
*	Crawler Devil Class
*/
Crawler::Crawler() {
	this->m_Sprite = sf::Sprite(TextureHolder::GetTexture(
		"graphics\\crawler.png"));

	this->m_Speed = CRAWLER_SPEED;
	this->m_Health = CRAWLER_HEALTH;
}