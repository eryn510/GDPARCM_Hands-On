#pragma once
#include "IETSemaphore.h"
#include <vector>
#include <queue>
#include "IconObject.h"

struct DataHolder 
{
	IconObject* iconRef;
	float posX = 0.0f; float posY = 0.0f;
	bool occupied;
};

struct ArrowHolder 
{
	float posX = 0.0f; float posY = 0.0f;
};

class DataHandler
{
public:
	static DataHandler* getInstance();

	void initializeThreads(int searcherCount, int inserterCount);

public:
	IETSemaphore* InsertSem;
	IETSemaphore* mutex;

	std::vector<IconObject*> displayList;
	std::queue<IconObject*> displayBank;
	std::vector<DataHolder> DataList;
	std::vector<std::vector<ArrowHolder>> ArrowList;

private:
	DataHandler();
	DataHandler(DataHandler const&) {};             // copy constructor is private
	DataHandler& operator=(DataHandler const&) {};  // assignment operator is private
	static DataHandler* sharedInstance;
};

