#pragma once
#include "Debug.h"
#include "Core.h"
#include "NonCopyable.h"

class Singleton : public NonCopyable
{
public:
	static Singleton* GetInstance();
	virtual ~Singleton();

private:
	static Singleton* m_Instance;
};