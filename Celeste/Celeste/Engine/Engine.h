#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine
{

public:
	static GLuint SCREEN_WIDTH;
	static GLuint SCREEN_HEIGHT;
	const static GLfloat MS_PER_UPDATE;

	Engine();
	~Engine();

	bool Init(char* _windowTitle);

	void Update();

	static double GetDT();
	//temp function
	GLFWwindow* GetWindow();

private:
	static GLFWwindow* window;
	static double dt;
	double lastTime;
	
};

#endif
