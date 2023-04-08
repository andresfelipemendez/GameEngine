#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <direct.h>
	#define chdir _chdir
	#define getcwd _getcwd
#else
	#include <unistd.h>
#endif

int main(int argc, char const *argv[])
{
	int result;

	printf("Creating build directory...\n");
	result = system("mkdir build");
	if(result != 0) {
		printf("Error creating build directory.\n");
		//return 1;
	}

	char cwd[FILENAME_MAX];
	if(getcwd(cwd,sizeof(cwd)) != NULL){
		printf("Current working directory: %s\n",cwd);
	} else {
		perror("getcwd() error");
		return 1;
	}
	
	const char* relative_build_dir = "build";
	if(chdir(relative_build_dir) == 0){
		printf("Changed working directory to: %s\n",relative_build_dir);
	} else {
		perror("chdir() error");
		return 1;
	}

	printf("Running CMake...\n");
	result = system("cmake -G \"Visual Studio 17 2022\" -A x64 -DCMAKE_TOOLCHAIN_FILE=\"~/vcpkg/scripts/buildsystems/vcpkg.cmake\" ..");
	if(result != 0) {
		printf("Error running CMake.\n");
		return 1;
	}

	printf("Building project...\n");
	result = system("cmake --build . --config Release");
	if(result != 0) {
		printf("Error build project.\n");
		return 1;
	}

	printf("Build successful!\n");
	return 0;
}