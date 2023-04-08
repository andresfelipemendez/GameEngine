#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char const *argv[])
{
	if(!glfwInit())
		return;

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	int monitorCount;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	// my work station have 3 monitors and I choose my third one
	// to display full screen the game
	int monitorIndex = monitorCount != 3 ? 0 : 2;
	GLFWmonitor* monitor = monitors[monitorIndex];
	int xpos, ypos;
	glfwGetMonitorPos(monitor, &xpos,&ypos);

	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	int monitorWidth = mode->width;
	int monitorHeight = mode->height;

	GLFWwindow* window = glfwCreateWindow(monitorWidth,monitorHeight,"Game Engine",NULL,NULL);
	if(!window)
	{
		glfwTerminate();
	}

	glfwSetWindowPos(window,xpos,ypos);
	glfwMakeContextCurrent(window);

	glClearColor(0.2f,0.5f,0.3f,1.0f);
	
	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}