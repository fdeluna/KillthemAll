#ifndef Gun_H
#define Gun_H

#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "WaveManager.h"
#include "SceneNodeComponent.h"
#include "RigidBodyComponent.h"
#include "AudioManager.h"

using namespace Ogre;

class Gun : public GameObject
{
public:

	Gun() : _sceneNodeComponentGun(nullptr), _rigidBodyComponentGun(nullptr){};
	Gun(Player* player, Ogre::SceneManager* sceneManager, Ogre::Vector3 position, Ogre::String mesh);	
	~Gun();

	void update(const Ogre::FrameEvent& evt);
	void upgrade();
	void shoot();
	void reload();

	void setCanShoot(bool shoot){ _canShoot = shoot; };
	void setReloading(bool reload){ _reloading = reload; };
	bool getReloading(){ return _reloading; };
	float getVelAtack(){ return _velAtack; };
	int getAmmo(){ return _ammo; };
	void setLevelGun(int _level){ _level = _level; };
	int getLevelGun(){ return _level; };
	int getNumBullet(){ return _numBullet; };

protected:
	
	int _numBullet;	
	Player* _player;
	SceneNodeComponent* _sceneNodeComponentGun;
	RigidBodyComponent* _rigidBodyComponentGun;
	AudioManager* _audioManager;
	bool _canShoot = true;
	float _velAtack = ATTACKVELOCITIES[AttackVelocity::SLOW];	
	int _level = 1;	
	int _ammo = 12;
	bool _reloading = false;	
};

#endif