#include "StateInAir.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"

CelesteState* StateInAir::HandleInput(Celeste& _celeste)
{
	int newDirection = 0;
	if (Keyboard::Key(GLFW_KEY_D))
	{
		newDirection++;
	}
	if (Keyboard::Key(GLFW_KEY_A))
	{
		newDirection--;
	}

	if (_celeste.direction == -1 && newDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandRight");
	}
	else if (_celeste.direction == 1 && newDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandLeft");
	}

	if (newDirection != 0)
	{
		_celeste.direction = newDirection;
	}

	_celeste.vel.x = (GLfloat)newDirection * _celeste.GetSpeed();

	return nullptr;
}

void StateInAir::Enter(Celeste& _celeste)
{
	if (_celeste.direction == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandRight");
	}
	else if (_celeste.direction == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandLeft");
	}
}

LocationState StateInAir::GetState()
{
	return LocationState::IN_AIR;
}