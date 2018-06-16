#include "Game.h"

#include "../Engine/Engine.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Graphics/SpriteRenderer.h"
#include "../Engine/Graphics/PostProcessor.h"
#include "../Engine/Graphics/TextRenderer.h"
#include "../Engine/IO/Keyboard.h"
#include "Celeste.h"
#include "RoomManager.h"
#include "Room.h"

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
RoomManager* rm;

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
	delete rm;
	rm = nullptr;
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
	ResourceManager::LoadTexture("Assets/Textures/Outline.png", GL_TRUE, "Exit");
	ResourceManager::LoadTexture("Assets/Textures/Ground.png", GL_TRUE, "Ground");
	ResourceManager::LoadTexture("Assets/Textures/VerticalGround.png", GL_TRUE, "VGround");
	ResourceManager::LoadTexture("Assets/Textures/HorizontalGround.png", GL_TRUE, "HGround");
	ResourceManager::LoadTexture("Assets/Textures/PassablePlatform.png", GL_TRUE, "PassablePlatform");
	ResourceManager::LoadTexture("Assets/Textures/Accelerator.png", GL_TRUE, "Accelerator");
	ResourceManager::LoadTexture("Assets/Textures/Chain.png", GL_TRUE, "Chain");
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
	glm::vec2 playerPos = glm::vec2(50.0f, 625.0f);
	celeste = new Celeste(playerPos, glm::vec2(30.0f, 60.0f), ResourceManager::GetTexture("StandRight"));

	//Load Room Objects
	rm = new RoomManager();
	rm->Init(3);
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
	Room* currentRoom = rm->GetCurrentRoom();
	celeste->Update(_dt);
	currentRoom->Update(_dt);

	celeste->ResolveCollision(currentRoom->GetRoomObjects());
	currentRoom->ResolveCollisions(*celeste);
}

void Game::Render()
{
	Room* currentRoom = rm->GetCurrentRoom();
	postProcessor->BeginRender();
	
	spriteRenderer->DrawSprite(ResourceManager::GetTexture("Background"), glm::vec2(0.0f, 0.0f), glm::vec2(width, height));
	currentRoom->Render(*spriteRenderer);
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