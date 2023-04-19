#include "DataHandler.h"
#include "DeleterThread.h"
#include "InserterThread.h"
#include "SearcherThread.h"
#include <fstream>

//a singleton class
DataHandler* DataHandler::sharedInstance = NULL;

DataHandler* DataHandler::getInstance()
{
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new DataHandler();
	}

	return sharedInstance;
}


DataHandler::DataHandler()
{
	for (int i = 1; i <= 10; i++) 
	{
		DataHolder holder;

		int IMG_WIDTH = 68; int IMG_HEIGHT = 68;

		holder.posX = i * IMG_WIDTH;
		holder.posY = 1 * IMG_HEIGHT;
		holder.occupied = false;
		
		this->DataList.push_back(holder);
	}

	for (int i = 2; i <= 10; i++) 
	{
		std::vector<ArrowHolder> vectorHolder;

		for (int j = 1; j <= 10; j++)
		{
			ArrowHolder holder;

			int IMG_WIDTH = 68; int IMG_HEIGHT = 68;

			holder.posX = j * IMG_WIDTH;
			holder.posY = i * IMG_HEIGHT;

			vectorHolder.push_back(holder);
		}

		this->ArrowList.push_back(vectorHolder);
	}
	
}

void DataHandler::initializeThreads(int searcherCount, int inserterCount)
{
	//Initialize Semaphores
	InsertSem = new IETSemaphore(0);
	mutex = new IETSemaphore(1);

	int counter = 0;

	//Clear txt file every run
	std::ofstream ofs("logs.txt", std::ios::trunc);
	ofs.close();

	//Initialize Searchers
	for (int i = 0; i < searcherCount; i++) 
	{
		SearcherThread* searcher = new SearcherThread(i, counter);
		searcher->start();
		counter++;
		IETThread::sleep(500);
	}

	//Initialize Inserter
	for (int i = 0; i < inserterCount; i++)
	{
		InserterThread* inserter = new InserterThread(i, counter);
		inserter->start();
		counter++;
	}

	//Initialize Deleter
	DeleterThread* deleter = new DeleterThread(0, counter);
	deleter->start();
}

