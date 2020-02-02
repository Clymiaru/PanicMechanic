#pragma once
#include "Debug.h"
#include "Core.h"
#include "Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();

	void LoadResources();
	void LoadObjects();
	void UnloadObjects();
	void UnloadResources();
};

