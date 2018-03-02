#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine
{

public:
	static GLuint SCREEN_WIDTH;
	static GLuint SCREEN_HEIGHT;

	Engine();
	~Engine();

	bool Init(char* _windowTitle);

	void Update();

	static GLfloat GetDT();
	//temp function
	GLFWwindow* GetWindow();

private:
	static GLFWwindow* window;
	static GLfloat dt;
	GLfloat lastTime;
	
};

#endif
