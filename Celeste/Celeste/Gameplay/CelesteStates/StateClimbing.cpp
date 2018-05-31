#include "StateClimbing.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateInAir.h"
#include "StateDashing.h"

#include <iostream>

CelesteState* StateClimbing::HandleInput(Celeste& _celeste)
{
	if (Keyboard::KeyUp(GLFW_KEY_COMMA) || !_celeste.CanClimb())
	{
		return new StateInAir();
	}

	if (Keyboard::KeyDown(GLFW_KEY_N) && _celeste.CanWallJump())
	{
		_celeste.MaxSpeedUp();
		_celeste.vel.y = -_celeste.JUMP_FORCE;
		_celeste.vel.x -= (GLfloat)_celeste.facingDirection * _celeste.JUMP_FORCE;
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

	return nullptr;
}

void StateClimbing::Update(Celeste & _celeste, GLfloat _dt)
{
	//apply friction
	if (Keyboard::KeyUp(GLFW_KEY_W) || Keyboard::KeyUp(GLFW_KEY_S) || !(Keyboard::Key(GLFW_KEY_W)
		|| Keyboard::Key(GLFW_KEY_S)) || (Keyboard::Key(GLFW_KEY_W) && Keyboard::Key(GLFW_KEY_S)))
	{
		_celeste.GetPhysicsComponent().ApplyGroundFriction(glm::vec2(0.0f, 1.0f));
	}

	_celeste.vel.y += (GLfloat)_celeste.direction.y * _celeste.ACCELERATION * _dt;

	//calculate timer increment
	if (_celeste.direction.y == -1)
	{
		_celeste.climbTimer += _dt * 3.0f;
	}
	else
	{
		_celeste.climbTimer += _dt;
	}
}

void StateClimbing::Enter(Celeste & _celeste)
{
	if (_celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("ClimbRight");
	}
	else if (_celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("ClimbLeft");
	}
	_celeste.GetLocationState() = LocationState::CLIMBING;
}

