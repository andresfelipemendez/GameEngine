#include "Library.h"

#include <Engine.h>

#include <iostream>

#include <chrono>
#include <thread>


#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void reloadLibrary(HINSTANCE& lib, Engine* engine, void* engineMemory, ExecutableAllocator& allocator, FILETIME& lastWriteTime) {
	while (true) {
		
		WIN32_FILE_ATTRIBUTE_DATA fileInfo;
		GetFileAttributesEx(L"engineLib.dll", GetFileExInfoStandard, &fileInfo);
		if (CompareFileTime(&fileInfo.ftLastWriteTime, &lastWriteTime) != 0)
		{
		
			if (CompareFileTime(&lastWriteTime, &lastWriteTime) != 0) {
				std::cout << "Reloading library" << std::endl;
				FreeLibrary(lib);
				lib = LoadLibrary(L"engineLib.dll");
				if (!lib) {
					std::cerr << "Failed to load library" << std::endl;
					return;
				}

				engine = new(engineMemory) Engine(&allocator);
				lastWriteTime = fileInfo.ftLastWriteTime;
			}

		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

Library::Library()
{
	lib = LoadLibrary(L"engineLib.dll");
	if (!lib) {
		std::cerr << "Failed to load library" << std::endl;
		return;
	}
	WIN32_FILE_ATTRIBUTE_DATA fileInfo;
	GetFileAttributesEx(L"engineLib.dll", GetFileExInfoStandard, &fileInfo);
	FILETIME lastWriteTime = fileInfo.ftLastWriteTime;


	engineMemory = allocator.allocate(sizeof(Library));
	engine = new(engineMemory) Engine(&allocator);
	engine->Init();

	// create a thread to check if the library was updated
	std::thread t(reloadLibrary, std::ref(lib), std::ref(engine), engineMemory, std::ref(allocator), std::ref(lastWriteTime));

}

Library::~Library()
{
	engine->~Engine();
	allocator.deallocate(engineMemory);

}

