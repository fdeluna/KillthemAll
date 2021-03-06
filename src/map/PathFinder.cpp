#include "PathFinder.h"

template<> PathFinder* Ogre::Singleton<PathFinder>::msSingleton = 0;

void PathFinder::FindPath(Ogre::Vector3 origin, Ogre::Vector3 destiny, std::vector<MapNode*>& path){

	MapNode* startNode = _currentMap->nodeFromWorldPosition(origin);
	MapNode* targetNode = _currentMap->nodeFromWorldPosition(destiny);
	if (startNode && targetNode){
		std::vector<MapNode*> openSet;
		std::vector<MapNode*> closeSet;		

		openSet.push_back(startNode);
		std::make_heap(openSet.begin(), openSet.end());


		while (openSet.size() > 0 && path.size() <= 0){
			MapNode* currentNode = openSet[0];

			openSet.erase(std::remove(openSet.begin(), openSet.end(), currentNode), openSet.end());
			closeSet.push_back(currentNode);

			if (currentNode == targetNode){
				MapNode* endNode = targetNode;
				while (endNode != startNode){
					path.push_back(endNode);					
					endNode = endNode->getParent();
				}
				std::reverse(path.begin(), path.end());
			}
			if (path.size() <= 0){
				for (MapNode* neighbour : _currentMap->getNeighbours(currentNode)){
					if (neighbour->isWakable() && std::find(closeSet.begin(), closeSet.end(), neighbour) == closeSet.end()){

						int movementCostToNeighbour = currentNode->getG() + getDistance(currentNode, neighbour);

						if (movementCostToNeighbour < neighbour->getG() || std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()){
							neighbour->setG(movementCostToNeighbour);
							neighbour->setH(getDistance(neighbour, targetNode));
							neighbour->setParent(currentNode);

							if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()){
								openSet.push_back(neighbour);
								std::sort(openSet.begin(), openSet.end(), lesserNode);
							}
						}
					}
				}
			}
		}
	}
}

int PathFinder::getDistance(MapNode* nodeA, MapNode* nodeB){

	int distance = 0;

	int distanceX = Ogre::Math::Abs(nodeA->getGridX() - nodeB->getGridX());
	int distanceY = Ogre::Math::Abs(nodeA->getGridY() - nodeB->getGridY());	

	if (distanceX > distanceY){
		distance = 10 * distanceY + 10 * (distanceX - distanceY);
	}
	else{
		distance = 10 * distanceX + 10 * (distanceY - distanceX);
	}

	return distance;
}

bool PathFinder::lesserNode(MapNode* a, MapNode* b)
{
	return a->getTotalCost() < b->getTotalCost();
}


PathFinder* PathFinder::getSingletonPtr() {
	return msSingleton;
}

PathFinder& PathFinder::getSingleton() {
	assert(msSingleton);
	return *msSingleton;
}