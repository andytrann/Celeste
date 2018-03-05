#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	Game(GLuint _width, GLuint _height);
	~Game();

	void Init();
	void ProcessInput();
	void Update(GLfloat _dt);
	void Render();
	void Reset();

	GLboolean IsGameClosed();
	GameState state;
private:

	GLuint width, height;
	GLboolean gameClosed;
};

#endif