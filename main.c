#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char const *argv[])
{
	if(!glfwInit()){
		printf("failed to initialize glfw\n");
		return;
	}

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

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
		printf("null window\n");
	}

	glfwSetWindowPos(window,xpos,ypos);
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		printf("failed to initialize GLAD");
		return -1;
	}

	glClearColor(0.7f,0.7f,0.3f,1.0f);

	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	printf("exit\n");
	return 0;
}