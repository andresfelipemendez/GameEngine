#pragma once

#include "ExecutableAllocator.h"

#ifdef ENGINELIB_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

struct GLFWwindow;

class MYLIBRARY_API Engine
{
public:
	Engine(ExecutableAllocator* allocator);
	~Engine();

	void Init();
	void Update();
	void Render();
	void Shutdown();
private:
	ExecutableAllocator* m_allocator;

	GLFWwindow* window =  nullptr;
};