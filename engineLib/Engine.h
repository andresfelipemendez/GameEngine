#pragma once




struct GLFWwindow;

class Engine
{
public:
	GLFWwindow* window = nullptr;
	Engine();
	~Engine();

	void Init();
	void Update();
	void Render();
	void Shutdown();

};