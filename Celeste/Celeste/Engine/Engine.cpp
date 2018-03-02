#include "Engine.h"

#include "IO\Keyboard.h"

#include <iostream>

using namespace std;

GLuint Engine::SCREEN_WIDTH = 1024;
GLuint Engine::SCREEN_HEIGHT = 768;

GLFWwindow* Engine::window = nullptr;
GLfloat Engine::dt = 0.0f;

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::Init(char* _windowTitle)
{
	if (!glfwInit())
	{
		cout << "Error initializing GLFW" << endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, _windowTitle, nullptr, nullptr);
	if (window == NULL)
	{
		cout << "Error creating window" << endl;
		return false;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	glfwSetKeyCallback(window, Keyboard::KeyCallback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	lastTime = (GLfloat)glfwGetTime();

	return true;
}

void Engine::Update()
{
	GLfloat now = (GLfloat)glfwGetTime();
	dt = now - lastTime;
	lastTime = now;
	glfwPollEvents();
}

GLfloat Engine::GetDT()
{
	return dt;
}

GLFWwindow* Engine::GetWindow()
{
	return window;
}
