#pragma once

#include <ExecutableAllocator.h>
#include <string>
#include <thread>

class Engine;

class Library
{
public:


	const std::wstring srcPath = L"engineLib.dll";
	const std::wstring destPath = L"copyEngineLib.dll";

	Engine* engine = nullptr;
	void* engineMemory = nullptr;
	HINSTANCE lib;
	ExecutableAllocator allocator;
	std::thread t;

	Library();
	~Library();

	void reloadLibrary(HINSTANCE& lib, Engine* engine, void* engineMemory, ExecutableAllocator& allocator);
};

