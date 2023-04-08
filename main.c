#include <GLFW/glfw3.h>

int main(int argc, char const *argv[])
{
	if(!glfwInit())
		return;

	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	return 0;
}