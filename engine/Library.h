#pragma once

#include <ExecutableAllocator.h>
class Engine;

class Library
{
public:
	Engine* engine = nullptr;
	void* engineMemory = nullptr;
	HINSTANCE lib;
	ExecutableAllocator allocator;

	Library();
	~Library();

};

