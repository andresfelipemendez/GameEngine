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

	int monitorCount;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

	GLFWmonitor* leftmostMonitor = monitors[0];
	int leftmostPos = INT_MAX;

	for (int i = 0; i < monitorCount;++i)
	{
		int xpos, ypos;
		glfwGetMonitorPos(monitors[i], &xpos, &ypos);
		if (xpos < leftmostPos) {
			leftmostPos = xpos;
			leftmostMonitor = monitors[i];
		}
	} 

	const GLFWvidmode* mode = glfwGetVideoMode(leftmostMonitor);
	int monitorWidth = mode->width;
	int monitorHeight = mode->height;

	window = glfwCreateWindow(monitorWidth, monitorHeight, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}

	glfwSetWindowPos(window, leftmostPos, 0);
	glfwMakeContextCurrent(window);


	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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