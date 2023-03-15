#include "Library.h"

#include <Engine.h>

#include <iostream>

#include <chrono>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void reloadLibrary(HINSTANCE& lib, Engine* engine, void* engineMemory, ExecutableAllocator& allocator) {
	

	while (true) {

		std::filesystem::path engineLibrary("engineLib.dll");
		if(std::filesystem::exists(engineLibrary))
		{
			std::cout << "Reloading library" << std::endl;

			FreeLibrary(lib);

			if (!MoveFileEx(L"engineLib", L"copyEngineLib.dll", MOVEFILE_REPLACE_EXISTING)) {
				std::wcerr << L"Failed to replace file: " << L"copyEngineLib.dll" << std::endl;
			}

			lib = LoadLibrary(L"copyEngineLib.dll");
			if (!lib) {
				std::cerr << "Failed to load library" << std::endl;
				return;
			}

			engine = new(engineMemory) Engine(&allocator);
			
			std::cerr << "reloaded library" << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void demo_perms(std::filesystem::perms p) {
	using std::filesystem::perms;
	auto show = [=](char op, perms perm)
	{
		std::cout << (perms::none == (perm & p) ? '-' : op);
	};
	show('r', perms::owner_read);
	show('w', perms::owner_write);
	show('x', perms::owner_exec);
	show('r', perms::group_read);
	show('w', perms::group_write);
	show('x', perms::group_exec);
	show('r', perms::others_read);
	show('w', perms::others_write);
	show('x', perms::others_exec);
	std::cout << '\n';
}

void copyEngineLibrary() {
	std::wstring srcPath(L"engineLib.dll");
	std::wstring destPath(L"copyEngineLib.dll");

	if (!MoveFileEx(srcPath.c_str(), destPath.c_str(), MOVEFILE_REPLACE_EXISTING)) {
		std::wcerr << L"Failed to replace file: " << srcPath << std::endl;
	}
}

Library::Library()
{
	copyEngineLibrary();
	
	lib = LoadLibrary(L"copyEngineLib.dll");
	if (!lib) {
		std::cerr << "Failed to load library" << std::endl;
		return;
	}

	engineMemory = allocator.allocate(sizeof(Library));
	engine = new(engineMemory) Engine(&allocator);
	engine->Init();

	t = std::thread(reloadLibrary, std::ref(lib), std::ref(engine), engineMemory, std::ref(allocator));
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

