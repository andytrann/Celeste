#include "StateClimbing.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateInAir.h"
#include "StateDashing.h"

#include <iostream>

CelesteState* StateClimbing::HandleInput(Celeste& _celeste, GLfloat _dt)
{
	if (Keyboard::KeyUp(GLFW_KEY_COMMA) || !_celeste.CanClimb())
	{
		return new StateInAir();
	}
	
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

	//update direction
	_celeste.direction.x = newDirection.x;
	_celeste.direction.y = newDirection.y;

	//apply friction
	if (Keyboard::KeyUp(GLFW_KEY_W) || Keyboard::KeyUp(GLFW_KEY_S) || !(Keyboard::Key(GLFW_KEY_W)
		|| Keyboard::Key(GLFW_KEY_S)) || (Keyboard::Key(GLFW_KEY_W) && Keyboard::Key(GLFW_KEY_S)))
	{
		_celeste.vel.y *= _celeste.FRICTION;
	}

	_celeste.vel.y += (GLfloat)newDirection.y * _celeste.ACCELERATION * _dt;

	//calculate timer increment
	if (_celeste.direction.y == -1)
	{
		_celeste.climbTimer += _dt * 2.0f;
	}
	else
	{
		_celeste.climbTimer += _dt;
	}

	return nullptr;
}

void StateClimbing::Enter(Celeste & _celeste)
{
	_celeste.GetLocationState() = LocationState::CLIMBING;
}

