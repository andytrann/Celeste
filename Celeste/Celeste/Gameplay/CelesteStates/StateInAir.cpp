#include "StateInAir.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"

CelesteState* StateInAir::HandleInput(Celeste& _celeste, GLfloat _dt)
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