#include "Game.h"

#include "../Engine/Engine.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Graphics/SpriteRenderer.h"
#include "../Engine/Graphics/PostProcessor.h"
#include "../Engine/Graphics/TextRenderer.h"
#include "../Engine/IO/Keyboard.h"
#include "Celeste.h"
#include "Platform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <irrKlang.h>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>

using namespace irrklang;

SpriteRenderer* spriteRenderer;
PostProcessor* postProcessor;
TextRenderer* textRenderer;
ISoundEngine* soundEngine = createIrrKlangDevice();

Celeste* celeste;
Platform* ground;
Platform* ground2;
Platform* ground3;

std::vector<GameObject> platforms;

Game::Game(GLuint _width, GLuint _height) :
	state(GameState::GAME_MENU),
	width(_width),
	height(_height),
	gameClosed(false)
{

}

Game::~Game()
{
	delete spriteRenderer;
	spriteRenderer = nullptr;

	delete postProcessor;
	postProcessor = nullptr;

	delete textRenderer;
	textRenderer = nullptr;

	delete soundEngine;
	soundEngine = nullptr;

	delete celeste;
	celeste = nullptr;

	delete ground;
	ground = nullptr;

	delete ground2;
	ground2 = nullptr;

	delete ground3;
	ground3 = nullptr;
}

void Game::Init()
{
	//Load shaders
	ResourceManager::LoadShader("Engine/Graphics/Shaders/Sprite.vs", "Engine/Graphics/Shaders/Sprite.fs", nullptr, "sprite");
	ResourceManager::LoadShader("Engine/Graphics/Shaders/PostProcessing.vs", "Engine/Graphics/Shaders/PostProcessing.fs", nullptr, "postprocessing");

	//Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(width),
		static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	//Load textures
	ResourceManager::LoadTexture("Assets/Textures/Background.png", GL_TRUE, "Background");
	ResourceManager::LoadTexture("Assets/Textures/Ground.png", GL_TRUE, "Ground");
	ResourceManager::LoadTexture("Assets/Textures/StandLeft.png", GL_TRUE, "StandLeft");
	ResourceManager::LoadTexture("Assets/Textures/StandRight.png", GL_TRUE, "StandRight");
	ResourceManager::LoadTexture("Assets/Textures/CrouchLeft.png", GL_TRUE, "CrouchLeft");
	ResourceManager::LoadTexture("Assets/Textures/CrouchRight.png", GL_TRUE, "CrouchRight");

	//Set render-specific controls
	spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	postProcessor = new PostProcessor(ResourceManager::GetShader("postprocessing"), width, height);

	//Load text font
	textRenderer = new TextRenderer(width, height);
	textRenderer->Load("Assets/Fonts/arialbd.ttf", 32);

	//Load Celeste
	glm::vec2 playerPos = glm::vec2(500.0f, (height / 8));
	celeste = new Celeste(playerPos, glm::vec2(30.0f, 60.0f), ResourceManager::GetTexture("StandRight"));

	//Load Platforms
	ground = new Platform(glm::vec2(50.0f, Engine::SCREEN_HEIGHT * 7.0f / 8.0f), glm::vec2(300.0f, Engine::SCREEN_HEIGHT / 8.0f), ResourceManager::GetTexture("Ground"));
	ground2 = new Platform(glm::vec2(450.0f, Engine::SCREEN_HEIGHT * 6.5f / 8.0f), glm::vec2(300.0f, Engine::SCREEN_HEIGHT / 8.0f), ResourceManager::GetTexture("Ground"));
	ground3 = new Platform(glm::vec2(450.0f, Engine::SCREEN_HEIGHT * 2.0f/8.0f), glm::vec2(300.0f, Engine::SCREEN_HEIGHT / 8.0f), ResourceManager::GetTexture("Ground"));
	platforms.push_back(*ground);
	platforms.push_back(*ground2);
	platforms.push_back(*ground3);
}

void Game::ProcessInput()
{
	//put celestestate input handler in here
	celeste->HandleInput();

	if (Keyboard::KeyDown(GLFW_KEY_ESCAPE))
	{
		gameClosed = true;
	}
}

void Game::Update(GLfloat _dt)
{
	celeste->Update(_dt);
	ground->Update(_dt);
	ground2->Update(_dt);
	ground3->Update(_dt);
	celeste->DoCollision(platforms);
}

void Game::Render()
{
	postProcessor->BeginRender();
	
	spriteRenderer->DrawSprite(ResourceManager::GetTexture("Background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height));
	celeste->Render(*spriteRenderer);
	ground->Render(*spriteRenderer);
	ground2->Render(*spriteRenderer);
	ground3->Render(*spriteRenderer);

	postProcessor->EndRender();
	postProcessor->Render();
}

void Game::Reset()
{

}

GLboolean Game::IsGameClosed()
{
	return gameClosed;
}