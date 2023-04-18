#include "DeleterThread.h"
#include "DataHandler.h"
#include "IconObject.h"
#include "ArrowObject.h"
#include "ObjectManager.h"

DeleterThread::DeleterThread(int id, int holderIndex)
{
	this->id = id;
	this->holderIndex = holderIndex;
}

void DeleterThread::run()
{
	DataHandler* data = DataHandler::getInstance();

	ArrowObject* arrow = new ArrowObject("Deleter");
	arrow->setPosition(data->ArrowList[holderIndex][0].posX, data->ArrowList[holderIndex][0].posY);
	ObjectManager::getInstance()->addObject(arrow);

	while (true) 
	{
		IETThread::sleep(1000);

		//Semaphore Acquire
		data->mutex->acquire();


		srand(time(NULL));

		int randNum = rand() % data->DataList.size();

		while (data->DataList[randNum].occupied == false) 
		{
			randNum = rand() % data->DataList.size();
		}

		IconObject* icon = data->DataList[randNum].iconRef;
		arrow->setPosition(data->ArrowList[holderIndex][randNum].posX, data->ArrowList[holderIndex][randNum].posY);
		data->displayList.erase(data->displayList.begin() + randNum);
		data->displayBank.push(icon);

		std::cout << "\n ==================== DELETER ==================== " << std::endl;
		std::cout << "\nDeleted at index: " << randNum << std::endl;

		icon->setActive(false);

		data->DataList[randNum].iconRef = nullptr;
		data->DataList[randNum].occupied = false;

		//Semaphore Release
		data->InsertSem->release();
		data->mutex->release();
	}
	
}
