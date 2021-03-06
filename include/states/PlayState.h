#ifndef PlayState_H
#define PlayState_H

#include "GameState.h"
#include "WaveCompleteState.h"
#include "GameOverState.h"
#include "PhysicsManager.h"
#include "PathFinder.h"
#include "Player.h"
#include "Bullet.h"
#include "Gun.h"
#include "Mine.h"
#include "AudioManager.h"

#include <Ogre.h>
#include <OIS/OIS.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <btBulletDynamicsCommon.h>

class PlayState : public Ogre::Singleton<PlayState>, public GameState
{
public:
	PlayState(){};
	~PlayState(){};
	static PlayState& getSingleton();
	static PlayState* getSingletonPtr();

	void enter();
	void exit();
	void pause();
	void resume();

	void keyPressed(const OIS::KeyEvent &e);
	void keyReleased(const OIS::KeyEvent &e);
	void mouseMoved(const OIS::MouseEvent &e);
	void mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	void mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	
	bool frameStarted(const Ogre::FrameEvent &e);
	bool frameEnded(const Ogre::FrameEvent &e);
	
	CEGUI::MouseButton convertMouseButton(OIS::MouseButtonID id);	

	void init();
	void createGUI();
	void printTextGUI();
	void updateLevelWeapons();
	void hudLife();

private:	
	Ogre::Root *_root;
	Ogre::SceneManager *_sceneMgr;
	Ogre::Camera *_camera;
	Ogre::Viewport *_viewport;
	AudioManager* _audioManager;

	WaveManager* _waveManager;
	PhysicsManager* _physicsManager;
	PathFinder* _pathFinder;
	Player* _player;

	Bullet* _bullet;
	Gun* _gun;
	Mine* _mine;

	GameFlowState _state = GameFlowState::PLAY;

	float _deltaT = 0;	
	float _delay = 0;
	float _startDelay = 0;	
	float timer = 0;
	float timerReload = 0;		
		
	CEGUI::Window* playStateUI;
	CEGUI::Window* _vida1;
	CEGUI::Window* _vida2;
	CEGUI::Window* _vida3;
	CEGUI::Window* _vida4;
	CEGUI::Window* _vida5;
	CEGUI::Window* _vida6;
	CEGUI::Window* _vida7;
	CEGUI::Window* _vida8;

	CEGUI::Window* _turnText;
	 
	CEGUI::Window* _wave;
	CEGUI::Window* _enemies;
	CEGUI::Window* _bulletsGUI;
	CEGUI::Window* _minesGUI;
	CEGUI::Window* _potGUI;
	CEGUI::Window* _centralText;
	CEGUI::Window* _levelText;
	CEGUI::Window* _warning;

	bool activeWarning = false;
	float timerWarning = 0;		

	CEGUI::Window* _hud;
	CEGUI::Window* _hudLife;
	CEGUI::Window* _hudWeapons;
	CEGUI::Window* _hudWeaponsClub;
	CEGUI::Window* _hudWeaponsGun;
	CEGUI::Window* _hudWeaponsShotGun;
	
	float _time = 0;	
	int _numMines = 0;
	int _numPots = 0;

	//PARTICLES
	Ogre::ParticleSystem* _partSystemPotion;
	Ogre::SceneNode* _nodeParticlePotion;
	float _timeParticlePotion = 0.5;
	Ogre::ParticleSystem* _partSystemFire;
	Ogre::ParticleSystem* _partSystemFire2;
	Ogre::SceneNode* _nodeParticleFire;
	Ogre::SceneNode* _nodeParticleFire2;

	float timeParticleFire;
};

#endif
