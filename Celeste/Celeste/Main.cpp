#include "Engine/Engine.h"
#include "Gameplay/Game.h"
#include "Engine/ResourceManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <time.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((unsigned int)time(NULL));

	Engine engine;
	engine.Init("Celeste");

	Game celesteGame(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT);
	celesteGame.Init();

	while (!celesteGame.IsGameClosed())
	{
		celesteGame.ProcessInput();
		engine.Update();
		celesteGame.Update(engine.GetDT());
		celesteGame.Render();

		glfwSwapBuffers(engine.GetWindow());
	}
	ResourceManager::Clear();
	glfwTerminate();

	return 0;
}