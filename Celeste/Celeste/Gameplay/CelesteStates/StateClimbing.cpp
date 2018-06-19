#include "StateClimbing.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "../PhysicsComponent.h"
#include "StateInAir.h"
#include "StateDashing.h"

#include <iostream>

CelesteState* StateClimbing::HandleInput(Celeste& _celeste)
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

	PhysicsComponent& cPhys = _celeste.GetPhysicsComponent();
	//jump while climbing
	if (Keyboard::KeyDown(GLFW_KEY_N) && _celeste.CanWallJump())
	{
		//vertical jump
		if (_celeste.direction.x == 0)
		{
			cPhys.SetVelY(-Celeste::JUMP_FORCE * .8f);
			_celeste.StartInputLock(.25f);
			_celeste.climbTimer += 3.0f;
		}
		//diagonal jump
		else
		{
			cPhys.SetVelY(-Celeste::JUMP_FORCE);
			cPhys.SetVelX(-(GLfloat)_celeste.facingDirection * _celeste.MAX_SPEED);
			_celeste.direction.x = -_celeste.facingDirection;
			_celeste.StartInputLock(.2f);
		}
		return new StateInAir();
	}
	
	return nullptr;
}

void StateClimbing::Update(Celeste & _celeste, GLfloat _dt)
{
	PhysicsComponent& cPhys = _celeste.GetPhysicsComponent();
	//apply friction
	if (Keyboard::KeyUp(GLFW_KEY_W) || Keyboard::KeyUp(GLFW_KEY_S) || !(Keyboard::Key(GLFW_KEY_W)
		|| Keyboard::Key(GLFW_KEY_S)) || (Keyboard::Key(GLFW_KEY_W) && Keyboard::Key(GLFW_KEY_S)))
	{
		cPhys.ApplyGroundFriction(glm::vec2(0.0f, 1.0f));
	}

	//add vertical velocity if between max speeds
	if (cPhys.GetVelocity().y < Celeste::MAX_CLIMB_SPEED_DOWN && cPhys.GetVelocity().y > Celeste::MAX_CLIMB_SPEED_UP)
	{
		cPhys.Accelerate(glm::vec2(0.0f, (GLfloat)_celeste.direction.y * Celeste::ACCELERATION), _dt);
	}

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

