#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <Ogre.h>


template <typename T>
static void initBidimensionalVector(std::vector<std::vector<T>> &vector2, int width, int heigh){
	vector2.resize(width);

	for (int i = 0; i < vector2.size(); i++){
		vector2[i].resize(heigh);
	}
}

template <typename T>
static void shuffleArray(std::vector<std::vector<T>> &vector2) {
	std::srand(std::time(0));

	for (int i = 0; i < vector2.size(); i++){
		for (int j = 0; j < vector2[i].size(); j++){
			int x = rand() % (int)vector2.size();
			int y = rand() % (int)vector2[i].size();
			T tempItem = vector2[x][y];
			vector2[x][y] = vector2[i][j];
			vector2[i][j] = tempItem;

		}
	}
}

static Ogre::Plane& createPlane(Ogre::String name, Ogre::Real width, Ogre::Real heigh){

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(name,
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		width, heigh, 1, 1, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);

	return plane;
}

static Ogre::Vector3 lerp(Ogre::Vector3 &srcLocation, Ogre::Vector3 &destLocation, Ogre::Real Time)
{
	Ogre::Vector3 mDest;
	mDest.x = srcLocation.x + (destLocation.x - srcLocation.x) * Time;
	mDest.y = srcLocation.y + (destLocation.y - srcLocation.y) * Time;
	mDest.z = srcLocation.z + (destLocation.z - srcLocation.z) * Time;
	return mDest;
}

static int ogreNameNumber;

static void getOgreName(Ogre::String &name){
	ogreNameNumber++;
	name.append(Ogre::StringConverter::toString(ogreNameNumber));
}

#endif