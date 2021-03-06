#ifndef SCENENODECOMPONENT_H
#define SCENENODECOMPONENT_H

#include "Component.h"
#include "Enum.h"
#include "Utils.h"
#include <Ogre.h>

class SceneNodeComponent : public Component{
public:

	SceneNodeComponent() :_sceneManager(nullptr), _sceneNode(nullptr), _entity(nullptr){};
	SceneNodeComponent(Ogre::SceneManager* sceneManager, Ogre::String name, Ogre::String mesh, Ogre::Vector3 scale, Ogre::Vector3 position, Ogre::SceneNode* father = nullptr);

	~SceneNodeComponent();	
	
	Ogre::Entity* getEntity(){ return _entity; };
	Ogre::SceneNode* getSceneNode(){ return _sceneNode; };
	Ogre::SceneManager* getSceneManager(){ return _sceneManager; };

	void addChild(Ogre::SceneNode* child){ _sceneNode->addChild(child); };
	void setVisible(bool visible){ _sceneNode->setVisible(visible); };
	void setMaterialName(Ogre::String materialName);
	void setMesh(Ogre::String mesh);

private:
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _sceneNode;
	Ogre::Entity* _entity;
};

#endif