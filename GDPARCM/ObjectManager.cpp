#include <stddef.h>
#include "ObjectManager.h"

ObjectManager* ObjectManager::sharedInstance = NULL;

ObjectManager* ObjectManager::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new ObjectManager();
	}
	return sharedInstance;
}

void ObjectManager::update(sf::Time deltaTime) {
	for (int i = 0; i < objectList.size(); i++) {
		objectList[i]->Update(deltaTime);
	}

}

void ObjectManager::processInput(sf::Event event) {
	for (int i = 0; i < this->objectList.size(); i++) {
		//this->objectList[i]->processInput(event);
	}
}

void ObjectManager::draw(sf::RenderWindow* window) {
	for (int i = 0; i < objectList.size(); i++) {
		objectList[i]->Draw(window, sf::RenderStates::Default);
	}
}

void ObjectManager::addObject(AObject *obj)
{
	//this->guard.lock();

	this->objectList.push_back(obj);
}

void ObjectManager::deleteObject(AObject *obj)
{
	int index = 0;

	for (int i = 0; i < this->objectList.size(); i++) 
	{
		if (this->objectList[i] == obj)
		{
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->objectList.erase(this->objectList.begin() + index);
	}

	delete obj;
}

void ObjectManager::deleteObjectByName(std::string name)
{
	AObject* temp = findObjectByName(name);

	if (temp != NULL)
		delete temp;
}

AObject* ObjectManager::findObject(AObject *obj)
{
	AObject* temp = NULL;

	for (AObject* tempObj : this->objectList) 
	{
		if (tempObj == obj) 
		{
			temp = tempObj;
			break;
		}
	}

	return temp;
}

AObject* ObjectManager::findObjectByName(std::string name)
{
	AObject* temp = NULL;

	for (AObject* tempObj : this->objectList)
	{
		if (tempObj->getName() == name)
		{
			temp = tempObj;
			break;
		}
	}

	return temp;
}

int ObjectManager::getObjectCount()
{
	return this->objectList.size();
}

std::vector<AObject*>* ObjectManager::getObjectList()
{
	return &this->objectList;
}
