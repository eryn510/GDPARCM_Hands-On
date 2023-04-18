#pragma once
#include "AObject.h"
#include "IExecutionEvent.h"

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay: public AObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void Update(sf::Time deltaTime);

	// Inherited via IExecutionEvent
	virtual void onFinishedExecution() override;

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 50.0f; //greatly reduce streaming load delay to demonstrate performance drop.
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0;
	int numDisplayed = 0;
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	void spawnObject();

};

