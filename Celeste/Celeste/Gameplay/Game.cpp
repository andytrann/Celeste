#include "Game.h"

#include "../Engine/Engine.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Graphics/SpriteRenderer.h"
#include "../Engine/Graphics/PostProcessor.h"
#include "../Engine/Graphics/TextRenderer.h"
#include "../Engine/IO/Keyboard.h"
#include "Celeste.h"
#include "LevelObjects/Platform.h"
#include "LevelObjects/PassablePlatform.h"
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
Platform* ground4;
Platform* ground5;
Platform* ground6;
Platform* ground7;
Platform* ground8;
Platform* ground9;
Platform* ground10;
Platform* ground11;
Platform* ground12;
PassablePlatform* passPlat;
PassablePlatform* passPlat2;
PassablePlatform* passPlat3;
Spikes* spikes;
Spikes* spikes2;
Spikes* spikes3;
Spikes* spikes4;
Spikes* spikes5;
Spikes* spikes6;
Spikes* spikes7;
Spikes* spikes8;
Spikes* spikes9;
Spikes* spikes10;
Spikes* spikes11;
Spikes* spikes12;
Spikes* spikes13;
Spikes* spikes14;
Spikes* spikes15;
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
	delete ground4;
	ground4 = nullptr;
	delete ground5;
	ground5 = nullptr;
	delete ground6;
	ground6 = nullptr;
	delete ground7;
	ground7 = nullptr;
	delete ground8;
	ground8 = nullptr;
	delete ground9;
	ground9 = nullptr;
	delete ground10;
	ground10 = nullptr;
	delete ground11;
	ground11 = nullptr;
	delete ground12;
	ground11 = nullptr;

	delete passPlat;
	passPlat = nullptr;
	delete passPlat2;
	passPlat2 = nullptr;
	delete passPlat3;
	passPlat3 = nullptr;

	delete spikes;
	spikes = nullptr;
	delete spikes2;
	spikes2 = nullptr;
	delete spikes3;
	spikes3 = nullptr;
	delete spikes4;
	spikes4 = nullptr;
	delete spikes5;
	spikes5 = nullptr;
	delete spikes6;
	spikes6 = nullptr;
	delete spikes7;
	spikes7 = nullptr;
	delete spikes8;
	spikes8 = nullptr;
	delete spikes9;
	spikes9 = nullptr;
	delete spikes10;
	spikes10 = nullptr;
	delete spikes11;
	spikes10 = nullptr;
	delete spikes12;
	spikes10 = nullptr;
	delete spikes13;
	spikes10 = nullptr;
	delete spikes14;
	spikes10 = nullptr;
	delete spikes15;
	spikes10 = nullptr;

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
	ResourceManager::LoadTexture("Assets/Textures/VerticalGround.png", GL_TRUE, "VGround");
	ResourceManager::LoadTexture("Assets/Textures/HorizontalGround.png", GL_TRUE, "HGround");
	ResourceManager::LoadTexture("Assets/Textures/PassablePlatform.png", GL_TRUE, "PassablePlatform");
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

	//Load Level Objects
	ground = new Platform(glm::vec2(0.0f, 700.0f), glm::vec2(300.0f, 150.0f), 0.0f, ResourceManager::GetTexture("HGround"));
	ground2 = new Platform(glm::vec2(300.0f, 625.0f), glm::vec2(150.0f, 175.0f), 0.0f, ResourceManager::GetTexture("HGround"));
	ground3 = new Platform(glm::vec2(350.0f, 175.0f), glm::vec2(50.0f, 450.0f), 0.0f, ResourceManager::GetTexture("VGround"));
	ground12 = new Platform(glm::vec2(400.0f, 175.0f), glm::vec2(50.0f, 225.0f), 0.0f, ResourceManager::GetTexture("VGround"));
	ground4 = new Platform(glm::vec2(0.0f, 400.0f), glm::vec2(225.0f, 100.0f), 0.0f, ResourceManager::GetTexture("HGround"));
	ground5 = new Platform(glm::vec2(0.0f, 300.0f), glm::vec2(200.0f, 25.0f), 0.0f, ResourceManager::GetTexture("HGround"));
	ground6 = new Platform(glm::vec2(0.0f, 0.0f), glm::vec2(150.0f, 300.0f), 0.0f, ResourceManager::GetTexture("VGround"));
	ground7 = new Platform(glm::vec2(550.0f, 150.0f), glm::vec2(100.0f, 250.0f), 0.0f, ResourceManager::GetTexture("VGround"));
	ground8 = new Platform(glm::vec2(450.0f, 725.0f), glm::vec2(400.0f, 50.0f), 0.0f, ResourceManager::GetTexture("HGround"));
	ground9 = new Platform(glm::vec2(850.0f, 650.0f), glm::vec2(174.0f, 250.0f), 0.0f, ResourceManager::GetTexture("VGround"));
	ground10 = new Platform(glm::vec2(975.0f, 450.0f), glm::vec2(49.0f, 200.0f), 0.0f, ResourceManager::GetTexture("VGround"));
	ground11 = new Platform(glm::vec2(750.0f, 450.0f), glm::vec2(100.0f, 75.0f), 0.0f, ResourceManager::GetTexture("HGround"));

	passPlat = new PassablePlatform(glm::vec2(850.0f, 450.0f), glm::vec2(125.0f, 20.0f), ResourceManager::GetTexture("PassablePlatform"));
	passPlat2 = new PassablePlatform(glm::vec2(700.0f, 500.0f), glm::vec2(50.0f, 25.0f), ResourceManager::GetTexture("PassablePlatform"));
	passPlat3 = new PassablePlatform(glm::vec2(675.0f, 650.0f), glm::vec2(175.0f, 20.0f), ResourceManager::GetTexture("PassablePlatform"));

	spikes = new Spikes(glm::vec2(355.0f, 155.0f), glm::vec2(45.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes2 = new Spikes(glm::vec2(400.0f, 155.0f), glm::vec2(45.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes3 = new Spikes(glm::vec2(555.0f, 130.0f), glm::vec2(45.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes4 = new Spikes(glm::vec2(600.0f, 130.0f), glm::vec2(45.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes5 = new Spikes(glm::vec2(405.0f, 605.0f), glm::vec2(40.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes6 = new Spikes(glm::vec2(405.0f, 605.0f), glm::vec2(40.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes7 = new Spikes(glm::vec2(455.0f, 705.0f), glm::vec2(45.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes8 = new Spikes(glm::vec2(500.0f, 705.0f), glm::vec2(50.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes9 = new Spikes(glm::vec2(550.0f, 705.0f), glm::vec2(50.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes10 = new Spikes(glm::vec2(600.0f, 705.0f), glm::vec2(50.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes11 = new Spikes(glm::vec2(650.0f, 705.0f), glm::vec2(50.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes12 = new Spikes(glm::vec2(700.0f, 705.0f), glm::vec2(50.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes13 = new Spikes(glm::vec2(750.0f, 705.0f), glm::vec2(50.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));
	spikes14 = new Spikes(glm::vec2(800.0f, 705.0f), glm::vec2(45.0f, 20.0f), 0.0f, ResourceManager::GetTexture("Spikes"));

	gem = new Gem(glm::vec2(490.0f, 250.0f), glm::vec2(30.0f, 30.0f), ResourceManager::GetTexture("Gem"));

	objects.push_back(ground);
	objects.push_back(ground2);
	objects.push_back(ground3);
	objects.push_back(ground4);
	objects.push_back(ground5);
	objects.push_back(ground6);
	objects.push_back(ground7);
	objects.push_back(ground8);
	objects.push_back(ground9);
	objects.push_back(ground10);
	objects.push_back(ground11);
	objects.push_back(ground12);
	objects.push_back(passPlat);
	objects.push_back(passPlat2);
	objects.push_back(passPlat3);
	objects.push_back(spikes);
	objects.push_back(spikes2);
	objects.push_back(spikes3);
	objects.push_back(spikes4);
	objects.push_back(spikes5);
	objects.push_back(spikes6);
	objects.push_back(spikes7);
	objects.push_back(spikes8);
	objects.push_back(spikes9);
	objects.push_back(spikes10);
	objects.push_back(spikes11);
	objects.push_back(spikes12);
	objects.push_back(spikes13);
	objects.push_back(spikes14);
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