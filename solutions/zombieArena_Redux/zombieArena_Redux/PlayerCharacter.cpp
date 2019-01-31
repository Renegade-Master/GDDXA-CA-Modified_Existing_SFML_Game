/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2019/01/31	YYYY/MM/DD
*	@description	...
*/

#include "PlayerCharacter.h"

sf::FloatRect PlayerCharacter::getPosition() {
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f PlayerCharacter::getCenter() {
	return m_Position;
}