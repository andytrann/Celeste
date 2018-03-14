#include "StateInAir.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"

CelesteState* StateInAir::HandleInput(Celeste& _celeste, GLfloat _dt)
{
	//calculate new direction
	glm::ivec2 newDirection(0, 0);
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
	}

	//change sprite according to new direction
	if (_celeste.direction.x == -1 && newDirection.x == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpRight");
	}
	else if (_celeste.direction.x == 1 && newDirection.x == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpLeft");
	}

	//update direction
	if (newDirection.x != 0)
	{
		_celeste.direction.x = newDirection.x;
	}

	//apply friction
	if (Keyboard::KeyUp(GLFW_KEY_D) || Keyboard::KeyUp(GLFW_KEY_A) || !(Keyboard::Key(GLFW_KEY_D) 
		|| Keyboard::Key(GLFW_KEY_A)) || (Keyboard::Key(GLFW_KEY_D) && Keyboard::Key(GLFW_KEY_A)))
	{
		_celeste.vel.x *= _celeste.FRICTION;
	}
	_celeste.vel.x += (GLfloat)newDirection.x * _celeste.ACCELERATION * _dt * .75f;

	return nullptr;
}

void StateInAir::Enter(Celeste& _celeste)
{
	if (_celeste.direction.x == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpRight");
	}
	else if (_celeste.direction.x == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpLeft");
	}
}

LocationState StateInAir::GetState()
{
	return LocationState::IN_AIR;
}