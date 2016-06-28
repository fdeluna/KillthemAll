#include "Enemy.h"


Enemy::Enemy(Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh, Player* player,int level) : GameObject(sceneManager), _player(player),_level(level){

	_sceneNodeComponent = new SceneNodeComponent(_sceneManager, "Enemy", mesh, Ogre::Vector3(0.1, 0.25, 0.1), position);
	_rigidBodyComponent = new RigidBodyComponent((GameObject*)this, GameObjectType::ENEMY, _sceneNodeComponent);
	_pathFinderComponent = new EnemyPathFinderComponent(_rigidBodyComponent);	
	_state = EnemyState::MOVE;
	_type = GameObjectType::ENEMY;
	addComponent(_sceneNodeComponent);
	addComponent(_rigidBodyComponent);	
	audioController = AudioController::getSingletonPtr();
	audioController->playAudio(Audio::SPAWN);		
}




void Enemy::update(float deltaTime){

	if (_life <= 0){
		_state = EnemyState::DIE;
	}

	switch (_state)
	{
	case EnemyState::ATTACK:
		if (!attackDistance() & !attack(deltaTime)){
			_state = EnemyState::MOVE;
		}
		break;
	case EnemyState::MOVE:
		move(deltaTime);
		if (attackDistance()){
			_state = EnemyState::ATTACK;
		}
		break;
	case EnemyState::DIE:
		audioController->playAudio(Audio::KILLENEMY);
		//WaveManager::getSingletonPtr()->setEnemiesKilled(WaveManager::getSingletonPtr()->getEnemiesKilled + 1);
		_active = false;		
		die(deltaTime);
		break;
	case EnemyState::HITTED:
		audioController->playAudio(Audio::HITENEMY);
		hitted(deltaTime);
		break;
	default:
		break;
	}

	GameObject::update(deltaTime);
}

bool Enemy::attackDistance(){
	return _player->getPosition().distance(_rigidBodyComponent->getPosition()) <= 2;
}

void Enemy::move(float deltaTime){
	if (_pathFinderComponent){	
		_pathFinderComponent->update(deltaTime * _speed,_player->getPosition());
	}
}

void Enemy::hitted(float deltaTime){

	_timeStun = _timeStun + deltaTime;
	if (_timeStun>_stunMax){
		_timeStun = 0;
		EnemyState::MOVE;
	}
}

Enemy::~Enemy(){
	
	delete _pathFinderComponent;
	delete _rigidBodyComponent;
	delete _sceneNodeComponent;
	GameObject::~GameObject();
}