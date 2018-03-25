#include "StateInAir.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateDashing.h"

#include <iostream>

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

	//update direction
	_celeste.direction.x = newDirection.x;
	_celeste.direction.y = newDirection.y;

	//change sprite according to new direction
	if (_celeste.direction.x == 1 && _celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpRight");
		_celeste.facingDirection = 1;

		//in case celeste dash jumps and changes direction or wall jumps and changes facing direction (actual direction of jump isnt changed)
		_celeste.MaxSpeedDown();
	}
	else if (_celeste.direction.x == -1 && _celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpLeft");
		_celeste.facingDirection = -1;

		//in case celeste dash jumps and changes direction or wall jumps and changes facing direction (actual direction of jump isnt changed)
		_celeste.MaxSpeedDown();
	}

	//if x vel goes below 30, max speed goes back to normal (so you can't hold same direction after wall jump and get increase in horizontal speed)
	if (glm::abs<GLfloat>(_celeste.vel.x) < 30.0f)
	{
		_celeste.MaxSpeedDown();
	}

	//wall jump
	if (Keyboard::KeyDown(GLFW_KEY_N) && _celeste.CanWallJump())
	{
		_celeste.MaxSpeedUp();
		_celeste.vel.y = -_celeste.JUMP_FORCE;
		_celeste.vel.x -= (GLfloat)_celeste.facingDirection * _celeste.JUMP_FORCE;
	}

	//dash in air
	if (Keyboard::KeyDown(GLFW_KEY_M) && _celeste.UseDash())
	{
		//if not holding any direction, dash in current facing direction
		if (newDirection == glm::ivec2(0, 0))
		{
			_celeste.vel.y = 0.0f;
			_celeste.vel.x = (GLfloat)_celeste.facingDirection * Celeste::DASH_FORCE;
			return new StateDashing();
		}
		//dash in 45 degree angle
		else if (newDirection.x != 0 && newDirection.y != 0)
		{
			_celeste.vel = (glm::vec2)newDirection * glm::sin(glm::quarter_pi<GLfloat>()) * Celeste::DASH_FORCE;
			return new StateDashing();
		}
		//dash in 90 degree angle
		else
		{
			_celeste.vel = (glm::vec2)newDirection * Celeste::DASH_FORCE;
			return new StateDashing();
		}
	}

	//apply friction
	if (!(Keyboard::Key(GLFW_KEY_D) || Keyboard::Key(GLFW_KEY_A)) || (Keyboard::Key(GLFW_KEY_D) && Keyboard::Key(GLFW_KEY_A)))
	{
		_celeste.vel.x *=  _celeste.FRICTION * 2;
	}
	_celeste.vel.x += (GLfloat)newDirection.x * _celeste.ACCELERATION * _dt ;

	return nullptr;
}

void StateInAir::Enter(Celeste& _celeste)
{
	if (_celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpRight");
	}
	else if (_celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpLeft");
	}
	_celeste.GetLocationState() = LocationState::IN_AIR;
}