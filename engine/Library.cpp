#include "Library.h"

#include <Engine.h>

#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


struct GLFWwindow;

Library::Library()
{
	if (!MoveFileEx(srcPath.c_str(), destPath.c_str(), MOVEFILE_REPLACE_EXISTING)) {
		std::wcerr << L"Failed to replace file: " << srcPath << std::endl;
	}
	
	lib = LoadLibrary(destPath.c_str());
	if (!lib) {
		std::cerr << "Failed to load library" << std::endl;
		return;
	}

	engineMemory = allocator.allocate(sizeof(Library));
	engine = new(engineMemory) Engine(&allocator);

	t = std::thread(&Library::reloadLibrary, this, std::ref(lib), std::ref(engine), engineMemory, std::ref(allocator));

	engine->Init();
	engine->Update();
}

void Library::reloadLibrary(HINSTANCE& lib, Engine* engine, void* engineMemory, ExecutableAllocator& allocator) {
	std::cout << "Start library watch" << std::endl;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		DWORD fileattrib = GetFileAttributes(srcPath.c_str());

		if (fileattrib != INVALID_FILE_ATTRIBUTES)
		{
			std::cout << "Reloading library" << std::endl;
			if (!FreeLibrary(lib)) {
				DWORD error = GetLastError();
				std::cerr << "Failed to free library, error code: " << error << std::endl;
				continue;
			}
			else
			{
				std::cout << "success freeing the library" << std::endl;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			DWORD flags;
			if (GetHandleInformation(lib, &flags)) {
				std::cout << "success getting handle information" << std::endl;

				if (flags & HANDLE_FLAG_PROTECT_FROM_CLOSE)
				{
					std::cout << "HANDLE_FLAG_PROTECT_FROM_CLOSE" << std::endl;
				}
				if (flags & HANDLE_FLAG_INHERIT)
				{
					std::cout << "HANDLE_FLAG_INHERIT" << std::endl;
				}
			}
			else
			{
				DWORD error = GetLastError();
				std::cerr << "Failed to get handle information, error code: " << error << std::endl;
			}

			SetFileAttributes(destPath.c_str(), GetFileAttributes(destPath.c_str()) & ~FILE_ATTRIBUTE_READONLY);

			while (true)
			{
				if (!DeleteFile(destPath.c_str())) {
					DWORD error = GetLastError();
					std::cerr << "Failed to delete file. Error code: " << error << std::endl;
				}
				else
				{
					break;
				}
			}

			while (true)
			{
				if (!MoveFileEx(srcPath.c_str(), destPath.c_str(), MOVEFILE_REPLACE_EXISTING)) {
					DWORD error = GetLastError();
					std::wcerr << L"Failed to replace file: " << error << std::endl;
					continue;
				}
				else
				{
					break;
				}
				
			}
			std::cerr << "loading new library" << std::endl;
			lib = LoadLibrary(destPath.c_str());
			if (!lib) {
				std::cerr << "Failed to load library" << std::endl;
				continue;
			}

			GLFWwindow* window = engine->window;
			engine = new(engineMemory) Engine(&allocator);
			engine->window = window;
			engine->Update();
		}
	}

	std::cout << "exited?" << std::endl;
}

Library::~Library()
{
	if (t.joinable())
	{
		t.join();
	}
	engine->~Engine();
	allocator.deallocate(engineMemory);
}

