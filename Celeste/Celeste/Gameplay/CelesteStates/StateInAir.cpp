#include "StateInAir.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateDashing.h"

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
	}
	else if (_celeste.direction.x == -1 && _celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("JumpLeft");
		_celeste.facingDirection = -1;
	}

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
		_celeste.vel.x *=  _celeste.FRICTION;
	}
	_celeste.vel.x += (GLfloat)newDirection.x * _celeste.ACCELERATION * _dt * .75f;

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