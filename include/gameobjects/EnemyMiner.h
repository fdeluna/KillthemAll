#ifndef ENEMYMINER_H
#define ENEMYMINER_H

#include "Enemy.h"
#include "AudioManager.h"
#include "Mine.h"

class EnemyMiner : public Enemy{

public:
	EnemyMiner() : Enemy() {};
	EnemyMiner(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Map* map, int level, GameObjectType type) : Enemy(sceneManager, position, mesh, nullptr, level, type), _map(map){};		

	void update(float deltaTime);
	void collision(GameObject* gameObject);
	void move(float deltaTime);
	bool attack(float deltaTime);

private:
	Map* _map;
	Mine* _mine;

	Ogre::Vector3 _targetPosition = Ogre::Vector3::ZERO;
	Ogre::Vector3 _currentPosition = Ogre::Vector3::ZERO;

};
#endif