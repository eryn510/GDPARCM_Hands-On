#pragma once
#include <iostream>
#include "IWorkerAction.h"

class IExecutionEvent;
class StreamAssetLoader : public IWorkerAction
{
public:
	StreamAssetLoader(std::string path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

	std::string path;
	IExecutionEvent* execEvent;
};

