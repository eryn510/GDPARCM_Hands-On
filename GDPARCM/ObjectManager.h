#pragma once
#include <vector>
#include "AObject.h"
#include <mutex>

class ObjectManager
{
public:
	static ObjectManager* getInstance();

public:
	void draw(sf::RenderWindow* window);
	void update(sf::Time deltaTime);
	void processInput(sf::Event event);

public:
	void addObject(AObject *obj);
	void deleteObject(AObject *obj);
	void deleteObjectByName(std::string name);

	AObject* findObject(AObject *obj);
	AObject* findObjectByName(std::string name);

	int getObjectCount();
	std::vector<AObject*> *getObjectList();

private:
	ObjectManager() {};
	ObjectManager(ObjectManager const&) {};
	ObjectManager& operator=(ObjectManager const&) {};
	static ObjectManager* sharedInstance;

	std::vector<AObject*> objectList;

	typedef std::mutex Mutex;
	Mutex guard;
};

