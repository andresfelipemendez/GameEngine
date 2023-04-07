#include "Engine.h"

#include <iostream>


#include <glad/glad.h>
#include <GLFW/glfw3.h>

Engine::Engine()
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

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	int monitorCount;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	GLFWmonitor* bottomMonitor = monitors[2];
	int xpos, ypos;
	glfwGetMonitorPos(bottomMonitor, &xpos, &ypos);
		
	const GLFWvidmode* mode = glfwGetVideoMode(bottomMonitor);
	int monitorWidth = mode->width;
	int monitorHeight = mode->height;

	window = glfwCreateWindow(monitorWidth, monitorHeight, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}

	glfwSetWindowPos(window, xpos, ypos);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr,"Failed to initialize GLAD\n");

	}

	glEnable(GL_DEPTH_TEST);
}

void Engine::Update() 
{
	glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void Engine::Render() {

}

void Engine::Shutdown() {
	glfwTerminate();	
}