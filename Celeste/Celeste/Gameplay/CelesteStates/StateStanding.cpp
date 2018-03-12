#include "StateStanding.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateCrouching.h"
#include "StateInAir.h"

CelesteState* StateStanding::HandleInput(Celeste& _celeste)
{
	if (Keyboard::KeyDown(GLFW_KEY_S))
	{
		return new StateCrouching();
	}
	else if (Keyboard::KeyDown(GLFW_KEY_N))
	{
		_celeste.vel.y = -_celeste.GetJump();
		return new StateInAir();
	}
	else
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
}

void StateStanding::Enter(Celeste& _celeste)
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

LocationState StateStanding::GetState()
{
	return LocationState::ON_GROUND;
}