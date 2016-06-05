#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(GameObject* gameObject, GameObjectType type, SceneNodeComponent* sceneNodeComponent) : Component(gameObject), _shape(nullptr), _rigidBody(nullptr), _sceneNodeComponent(sceneNodeComponent){

	Ogre::Vector3 position = _sceneNodeComponent->getSceneNode()->getPosition();
	Ogre::Quaternion orientation = _sceneNodeComponent->getSceneNode()->getOrientation();

	OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = NULL;

	switch (type)
	{
	case OBSTACLE:
		_shape = new OgreBulletCollisions::BoxCollisionShape(Ogre::Vector3(0.5, 0.5, 0.5));
		break;
	case HELL:
		_shape = new OgreBulletCollisions::BoxCollisionShape(Ogre::Vector3(20, 0.5, 20));
		break;
	case MAP_FLOOR:
		trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(_sceneNodeComponent->getEntity());
		_shape = trimeshConverter->createConvex();
		break;
	case PLAYER:
		_shape = new OgreBulletCollisions::CapsuleCollisionShape(0.5, 1, Ogre::Vector3::UNIT_Y);
		break;
	}

	Ogre::String rigidName(_sceneNodeComponent->getSceneNode()->getName());
	rigidName.append("RigidBody");
	PhysicsManager* physicsMgr = PhysicsManager::getSingletonPtr();


	_rigidBody = new OgreBulletDynamics::RigidBody(rigidName, physicsMgr->getWorld());


	if (type != GameObjectType::PLAYER){
		_rigidBody->setStaticShape(_shape, 0.01, 1, position, orientation);
		_rigidBody->setGravity(Ogre::Vector3::ZERO);
	}
	else{
		_rigidBody->setShape(_sceneNodeComponent->getSceneNode(), _shape, 0.01, 1, 100.0, position, orientation);
		//_rigidBody->getBulletRigidBody()->setLinearFactor(btVector3(0, 0, 0));
		_rigidBody->getBulletRigidBody()->setAngularFactor(btVector3(0, 0, 0));
	}

	_rigidBody->disableDeactivation();

	_rigidBody->getBulletRigidBody()->setUserPointer(gameObject);
	setWorldPosition(position);
}

RigidBodyComponent::~RigidBodyComponent(){
	if (_rigidBody) {
		delete _rigidBody;
	}
	if (_shape) {
		delete _shape;
	}
}

Ogre::Vector3 RigidBodyComponent::getPosition(){

	return OgreBulletCollisions::BtOgreConverter::to(_rigidBody->getBulletRigidBody()->getWorldTransform().getOrigin());
}

Ogre::Quaternion RigidBodyComponent::getOrientation(){
	return OgreBulletCollisions::BtOgreConverter::to(_rigidBody->getBulletRigidBody()->getWorldTransform().getRotation());
}


void RigidBodyComponent::setWorldPosition(Ogre::Vector3 position){
	btTransform transform = _rigidBody->getBulletRigidBody()->getWorldTransform();
	transform.setOrigin(OgreBulletCollisions::OgreBtConverter::to(position)); //Set the new position/origin
	_rigidBody->getBulletRigidBody()->setWorldTransform(transform);
}

void RigidBodyComponent::setWorldOrientation(Ogre::Quaternion orientation){
	btTransform transform = _rigidBody->getBulletRigidBody()->getWorldTransform();
	transform.setRotation(OgreBulletCollisions::OgreBtConverter::to(orientation)); //Set the new position/origin
	_rigidBody->getBulletRigidBody()->setWorldTransform(transform);
}

void RigidBodyComponent::translate(Ogre::Vector3 direction){
	_rigidBody->getBulletRigidBody()->translate(OgreBulletCollisions::OgreBtConverter::to(direction));
}

void RigidBodyComponent::rotate(Ogre::Vector3 dest){

	Ogre::Vector3 source = getPosition();
	Ogre::Vector3 direcction = (dest - source).normalisedCopy();

	Ogre::Radian angle = source.angleBetween(direcction);
	
	;
	std::cout << "CROSS" << source.normalisedCopy().crossProduct(dest.normalisedCopy()) << std::endl;

	//return Quaternion.CreateFromAxisAngle(rotAxis, rotAngle);
}
