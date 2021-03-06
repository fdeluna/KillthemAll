#ifndef Map_H
#define Map_H

#include "GameObject.h"
#include "MapNode.h"
#include "Enum.h"
#include "Utils.h"

#include <Ogre.h>
#include <random>

class Map : public GameObject{

public:

	Map(Ogre::SceneManager* sceneManager) :GameObject(sceneManager){ _type = GameObjectType::HELL; }
	~Map(){ cleanMap();  GameObject::~GameObject(); };

	void GenerateMap();
	void cleanMap();
	Ogre::Vector2 getMapCenter(){ return _mapCenter;};	

	MapNode* nodeFromWorldPosition(Ogre::Vector3 position);;
	std::vector<MapNode*> getNeighbours(MapNode* node);

	std::vector<std::vector <MapNode*>> getGrid(){ return grid; };
	Ogre::Vector3 getRandomNodePosition();


private:
	Ogre::Vector2 _mapSize;
	Ogre::Vector2 _mapCenter;
	SceneNodeComponent* planeNode;
	RigidBodyComponent* rigidBodyComponent;
	std::vector< std::vector <MapNode*>> grid;

	bool isMapAccessible(std::vector< std::vector <bool>> obstacleMap, int currentNumberObstacle);

};

#endif