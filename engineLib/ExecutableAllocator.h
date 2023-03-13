#pragma once

#include <Windows.h>

class ExecutableAllocator {
public:
	void* allocate(size_t size) {
		return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}

	void deallocate(void* p) {
		VirtualFree(p, 0, MEM_RELEASE);
	}
};
