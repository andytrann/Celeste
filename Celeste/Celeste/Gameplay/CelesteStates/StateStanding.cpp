#include "StateStanding.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateCrouching.h"
#include "StateInAir.h"

CelesteState* StateStanding::HandleInput(Celeste& _celeste, GLfloat _dt)
{
	//calculate new direction
	glm::ivec2 newDirection(0,0);
	if (Keyboard::Key(GLFW_KEY_A))
	{
		newDirection.x--;
	}
	if (Keyboard::Key(GLFW_KEY_D))
	{
		newDirection.x++;
	}
	if (Keyboard::Key(GLFW_KEY_W))
	{
		newDirection.y--;
	}
	if (Keyboard::Key(GLFW_KEY_S))
	{
		newDirection.y++;
		_celeste.direction.y = 1;
		return new StateCrouching();
	}

	if (Keyboard::KeyDown(GLFW_KEY_N))
	{
		_celeste.vel.y = -_celeste.JUMP_FORCE;
		return new StateInAir();
	}

	//change sprite according to new direction
	if (_celeste.direction.x == -1 && newDirection.x == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandRight");
	}
	else if (_celeste.direction.x == 1 && newDirection.x == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandLeft");
	}

	//update direction
	if (newDirection.x != 0)
	{
		_celeste.direction.x = newDirection.x;
	}
	if (newDirection.y != 0)
	{
		_celeste.direction.y = newDirection.y;
	}

	//apply friction
	if (Keyboard::KeyUp(GLFW_KEY_D) || Keyboard::KeyUp(GLFW_KEY_A) || !(Keyboard::Key(GLFW_KEY_D) 
		|| Keyboard::Key(GLFW_KEY_A)) || (Keyboard::Key(GLFW_KEY_D) && Keyboard::Key(GLFW_KEY_A)))
	{
		_celeste.vel.x *= _celeste.FRICTION;
	}

	_celeste.vel.x += (GLfloat)newDirection.x * _celeste.ACCELERATION * _dt;

	return nullptr;
}

void StateStanding::Enter(Celeste& _celeste)
{
	if (_celeste.direction.x == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandRight");
	}
	else if (_celeste.direction.x == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandLeft");
	}
}

LocationState StateStanding::GetState()
{
	return LocationState::ON_GROUND;
}