#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void LoadResources();
	void LoadObjects();
	void UnloadObjects();
	void UnloadResources();

private:

};