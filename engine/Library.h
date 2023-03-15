#pragma once

#include <ExecutableAllocator.h>

#include <thread>
class Engine;

class Library
{
public:
	Engine* engine = nullptr;
	void* engineMemory = nullptr;
	HINSTANCE lib;
	ExecutableAllocator allocator;
	std::thread t;

	Library();
	~Library();

};

