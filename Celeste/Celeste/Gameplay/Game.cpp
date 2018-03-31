#include "Game.h"

#include "../Engine/Engine.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Graphics/SpriteRenderer.h"
#include "../Engine/Graphics/PostProcessor.h"
#include "../Engine/Graphics/TextRenderer.h"
#include "../Engine/IO/Keyboard.h"
#include "Celeste.h"
#include "LevelObjects/Platform.h"
#include "LevelObjects/Spikes.h"
#include "LevelObjects/Gem.h"

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
Spikes* spikes;
Gem* gem;

std::vector<GameObject*> objects;

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

	delete spikes;
	spikes = nullptr;

	delete gem;
	gem = nullptr;
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
	ResourceManager::LoadTexture("Assets/Textures/Spikes.png", GL_TRUE, "Spikes");
	ResourceManager::LoadTexture("Assets/Textures/Gem.png", GL_TRUE, "Gem");
	ResourceManager::LoadTexture("Assets/Textures/GemOutline.png", GL_TRUE, "GemOutline");
	ResourceManager::LoadTexture("Assets/Textures/StandLeft.png", GL_TRUE, "StandLeft");
	ResourceManager::LoadTexture("Assets/Textures/StandRight.png", GL_TRUE, "StandRight");
	ResourceManager::LoadTexture("Assets/Textures/CrouchLeft.png", GL_TRUE, "CrouchLeft");
	ResourceManager::LoadTexture("Assets/Textures/CrouchRight.png", GL_TRUE, "CrouchRight");
	ResourceManager::LoadTexture("Assets/Textures/JumpLeft.png", GL_TRUE, "JumpLeft");
	ResourceManager::LoadTexture("Assets/Textures/JumpRight.png", GL_TRUE, "JumpRight");
	ResourceManager::LoadTexture("Assets/Textures/DashLeft.png", GL_TRUE, "DashLeft");
	ResourceManager::LoadTexture("Assets/Textures/DashRight.png", GL_TRUE, "DashRight");
	ResourceManager::LoadTexture("Assets/Textures/ClimbLeft.png", GL_TRUE, "ClimbLeft");
	ResourceManager::LoadTexture("Assets/Textures/ClimbRight.png", GL_TRUE, "ClimbRight");

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
	ground2 = new Platform(glm::vec2(350.0f, Engine::SCREEN_HEIGHT * 6.5f / 8.0f), glm::vec2(300.0f, Engine::SCREEN_HEIGHT / 8.0f), ResourceManager::GetTexture("Ground"));
	ground3 = new Platform(glm::vec2(450.0f, Engine::SCREEN_HEIGHT * 2.0f/8.0f), glm::vec2(300.0f, Engine::SCREEN_HEIGHT / 8.0f), ResourceManager::GetTexture("Ground"));
	spikes = new Spikes(glm::vec2(500.0f, Engine::SCREEN_HEIGHT / 2.0f), glm::vec2(45.0f, 30.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	gem = new Gem(glm::vec2(300.0f, Engine::SCREEN_HEIGHT / 2.0f), glm::vec2(30.0f, 30.0f), ResourceManager::GetTexture("Gem"));
	objects.push_back(ground);
	objects.push_back(ground2);
	objects.push_back(ground3);
	objects.push_back(spikes);
	objects.push_back(gem);
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
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(_dt);
	}

	celeste->DoCollision(objects);
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i]->DoCollision(*celeste);
	}
}

void Game::Render()
{
	postProcessor->BeginRender();
	
	spriteRenderer->DrawSprite(ResourceManager::GetTexture("Background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height));
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(*spriteRenderer);
	}
	celeste->Render(*spriteRenderer);

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