/**
*	@author			Ciaran Bent	[K00221230]
*	@creationDate	2018/12/06	YYYY/MM/DD
*	@description	...
*/

#include "DevilSpawn.h"
#include "Devil.h"

std::vector<Devil*> createHorde(int numDevils, sf::IntRect arena) {
	std::vector<Devil*> horde(numDevils);

	srand((int)time(0));
	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (std::vector<Devil*>::iterator it = horde.begin(); it != horde.end(); ++it) {

		// Which side should the zombie spawn
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

		// Spawn the new zombie into the array
		(*it)->spawn(x, y, type);

	}
	return horde;
}
