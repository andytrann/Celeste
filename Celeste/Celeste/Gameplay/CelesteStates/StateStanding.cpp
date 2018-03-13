#include "StateStanding.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateCrouching.h"
#include "StateInAir.h"

CelesteState* StateStanding::HandleInput(Celeste& _celeste, GLfloat _dt)
{
	if (Keyboard::KeyDown(GLFW_KEY_S))
	{
		return new StateCrouching();
	}
	else if (Keyboard::KeyDown(GLFW_KEY_N))
	{
		_celeste.vel.y = -_celeste.JUMP_FORCE;
		return new StateInAir();
	}
	else
	{
		//calculate new direction
		int newDirection = 0;
		if (Keyboard::Key(GLFW_KEY_D))
		{
			newDirection++;
		}
		if (Keyboard::Key(GLFW_KEY_A))
		{
			newDirection--;
		}

		//change sprite according to new direction
		if (_celeste.direction == -1 && newDirection == 1)
		{
			_celeste.sprite = ResourceManager::GetTexture("StandRight");
		}
		else if (_celeste.direction == 1 && newDirection == -1)
		{
			_celeste.sprite = ResourceManager::GetTexture("StandLeft");
		}

		//update direction
		if (newDirection != 0)
		{
			_celeste.direction = newDirection;
		}

		//apply friction
		if (Keyboard::KeyUp(GLFW_KEY_D) || Keyboard::KeyUp(GLFW_KEY_A) || !(Keyboard::Key(GLFW_KEY_D) || Keyboard::Key(GLFW_KEY_A)))
		{
			_celeste.vel.x *= _celeste.FRICTION;
		}

		_celeste.vel.x += (GLfloat)newDirection * _celeste.ACCELERATION * _dt;

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