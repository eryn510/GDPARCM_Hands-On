#include "StreamAssetLoader.h"
#include <vector>
#include "StringUtils.h"
#include "TextureManager.h"
#include "IExecutionEvent.h"
#include "IETThread.h"

StreamAssetLoader::StreamAssetLoader(std::string path, IExecutionEvent* executionEvent): path(path), execEvent(executionEvent)
{

}

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "Destroying Stream Asset Loader" << std::endl;
}

void StreamAssetLoader::onStartTask()
{
	std::cout << "Running Stream Asset Loader" << std::endl;

	IETThread::sleep(1000);

	std::vector <std::string> tokens = StringUtils::split(path, '/');
	std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;


	this->execEvent->onFinishedExecution();
	//delete after being done
	delete this;
}
