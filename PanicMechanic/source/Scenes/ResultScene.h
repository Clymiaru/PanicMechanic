#pragma once
#include "Debug.h"
#include "Core.h"
#include "Scene.h"

class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();

	void LoadResources();
	void LoadObjects();
	void UnloadObjects();
	void UnloadResources();
};
