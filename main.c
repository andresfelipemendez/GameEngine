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

	

	return 0;
}