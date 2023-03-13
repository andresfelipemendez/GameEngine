#include "Engine.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <GL/gl.h>


Engine::Engine(ExecutableAllocator* allocator) :
	m_allocator(allocator)
{
	std::cout << "engine constructor" << std::endl;
}

Engine::~Engine() {
	std::cout << "engine destructor" << std::endl;
}

void Engine::Init() {
	std::cout << "engine init" << std::endl;


	if (!glfwInit())
		return;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	
	return;
}

void Engine::Update() {}
void Engine::Render() {}
void Engine::Shutdown() {
	glfwTerminate();
}