#pragma once
#include "Debug.h"
#include "Core.h"
#include "GameObjects/GameObject.h"
#include <string>
class Scene
{
public:
	Scene(const std::string& name);
	virtual ~Scene();

	virtual void LoadResources() = 0;
	virtual void LoadObjects() = 0;

	virtual void UnloadResources() = 0;
	virtual void UnloadObjects() = 0;

public:
	const std::string& GetName() const;
protected:
	void RegisterObject(Ref<GameObject> object);
	std::string SceneName;

};

