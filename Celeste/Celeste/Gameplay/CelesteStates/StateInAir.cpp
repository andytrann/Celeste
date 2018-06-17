#include "StateInAir.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "../PhysicsComponent.h"
#include "StateDashing.h"
#include "StateClimbing.h"

#include <iostream>

CelesteState* StateInAir::HandleInput(Celeste& _celeste)
{
	if (!_celeste.IsInputLocked())
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

		PhysicsComponent& cPhys = _celeste.GetPhysicsComponent();
		//wall jump
		if (Keyboard::KeyDown(GLFW_KEY_N) && _celeste.CanWallJump() && _celeste.direction.x != 0)
		{
			cPhys.SetVelY(-Celeste::JUMP_FORCE);
			cPhys.SetVelX(-(GLfloat)_celeste.direction.x * _celeste.MAX_SPEED);
			_celeste.direction.x *= -1;
			_celeste.StartInputLock(.2f);
		}

		//dash in air
		if (Keyboard::KeyDown(GLFW_KEY_M) && _celeste.UseDash())
		{
			cPhys.ResetVelX();
			cPhys.ResetVelY();
			//if not holding any direction, dash in current facing direction
			if (newDirection == glm::ivec2(0, 0))
			{
				cPhys.Accelerate(glm::vec2((GLfloat)_celeste.facingDirection * Celeste::DASH_FORCE, 0.0f), 1.0f);
				return new StateDashing();
			}
			//dash in 45 degree angle
			else if (newDirection.x != 0 && newDirection.y != 0)
			{
				cPhys.Accelerate((glm::vec2)newDirection * glm::sin(glm::quarter_pi<GLfloat>()) * Celeste::DASH_FORCE, 1.0f);
				return new StateDashing();
			}
			//dash in 90 degree angle
			else
			{
				cPhys.Accelerate((glm::vec2)newDirection * Celeste::DASH_FORCE, 1.0f);
				return new StateDashing();
			}
		}

		//climbing
		if (_celeste.CanClimb() && Keyboard::Key(GLFW_KEY_COMMA))
		{
			cPhys.ResetVelX();
			cPhys.ResetVelY();
			return new StateClimbing();
		}
	}
	
	return nullptr;
}

void StateInAir::Update(Celeste & _celeste, GLfloat _dt)
{
	PhysicsComponent& cPhys = _celeste.GetPhysicsComponent();
	//apply friction
	if (!(Keyboard::Key(GLFW_KEY_D) || Keyboard::Key(GLFW_KEY_A)) || (Keyboard::Key(GLFW_KEY_D) && Keyboard::Key(GLFW_KEY_A)))
	{
		cPhys.ApplyAirFriction();
	}

	//add horizontal velocity if below max speed
	if (abs(cPhys.GetVelocity().x) < Celeste::MAX_SPEED || 
		(abs(cPhys.GetVelocity().x) >= Celeste::MAX_SPEED && (cPhys.GetVelocity().x / _celeste.direction.x ) < 0.0f))
	{
		cPhys.Accelerate(glm::vec2((GLfloat)_celeste.direction.x * Celeste::ACCELERATION, 0.0f), _dt);
	}
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