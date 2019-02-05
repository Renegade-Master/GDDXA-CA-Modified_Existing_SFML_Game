/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	Creating hordes of Enemies.
*/

#include "DevilSpawn.h"
#include "Devil.h"

void DevilSpawn::createHorde(int numDevils, sf::IntRect arena) {
	//	THIS NEEDS REPLACING FAST
	srand((int)time(0));
	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numDevils; i++) {
		// Which side should the Enemy spawn
		int side = (rand() % 4);
		float x, y;

		switch (side) {
			case 0:
				// left
				x = minX;
				y = (rand() % maxY) + minY;
				break;

			case 1:
				// right
				x = maxX;
				y = (rand() % maxY) + minY;
				break;

			case 2:
				// top
				x = (rand() % maxX) + minX;
				y = minY;
				break;

			case 3:
				// bottom
				x = (rand() % maxX) + minX;
				y = maxY;
				break;
		}

		// Bloater, crawler or runner
		//srand((int)time(0) * 2);
		int type = (rand() % 3);

		horde.push_back(summonDevil(sf::Vector2f(x,y), type));
	}
}

Devil* DevilSpawn::summonDevil(sf::Vector2f pos, int type) {
	Devil* thrall = NULL;

	switch (type) {
	case 0:
		thrall = new Bloater();
		break;
	case 1:
		thrall = new Chaser();
		break;
	case 2:
		thrall = new Crawler();
		break;
	default:
		break;
	}
	
	// Spawn the new Enemy into the array
	thrall->spawn(pos.x, pos.y, type);

	return(thrall);

}
