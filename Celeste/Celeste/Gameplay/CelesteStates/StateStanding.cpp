#include "StateStanding.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateCrouching.h"
#include "StateInAir.h"
#include "StateDashing.h"
#include "StateClimbing.h"

CelesteState* StateStanding::HandleInput(Celeste& _celeste)
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
		_celeste.direction.x = newDirection.x;
		_celeste.direction.y = newDirection.y;
		return new StateCrouching();
	}

	//update direction
	_celeste.direction.x = newDirection.x;
	_celeste.direction.y = newDirection.y;

	//change sprite according to new direction
	if (_celeste.direction.x == 1 && _celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandRight");
		_celeste.facingDirection = 1;
	}
	else if (_celeste.direction.x == -1 && _celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandLeft");
		_celeste.facingDirection = -1;
	}

	PhysicsComponent& cPhys = _celeste.GetPhysicsComponent();
	//jump
	if (Keyboard::KeyDown(GLFW_KEY_N))
	{
		cPhys.ResetVelY();
		cPhys.Accelerate(glm::vec2(0.0f, -Celeste::JUMP_FORCE), 1.0f);
		return new StateInAir();
	}
	//dash
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
		//dash at 45 degree angle
		else if (newDirection.x != 0 && newDirection.y != 0)
		{
			cPhys.Accelerate((glm::vec2)newDirection * glm::sin(glm::quarter_pi<GLfloat>()) * Celeste::DASH_FORCE, 1.0f);
			return new StateDashing();
		}
		//dash at 90 degree angle
		else
		{
			cPhys.Accelerate((glm::vec2)newDirection * Celeste::DASH_FORCE, 1.0f);
			return new StateDashing();
		}
	}

	//climb
	if (_celeste.CanClimb() && Keyboard::KeyDown(GLFW_KEY_COMMA))
	{
		cPhys.ResetVelX();
		cPhys.ResetVelY();
		return new StateClimbing();
	}

	return nullptr;
}

void StateStanding::Update(Celeste& _celeste, GLfloat _dt)
{
	PhysicsComponent& cPhys = _celeste.GetPhysicsComponent();
	//apply friction
	if (Keyboard::KeyUp(GLFW_KEY_D) || Keyboard::KeyUp(GLFW_KEY_A) || !(Keyboard::Key(GLFW_KEY_D)
		|| Keyboard::Key(GLFW_KEY_A)) || (Keyboard::Key(GLFW_KEY_D) && Keyboard::Key(GLFW_KEY_A)))
	{
		cPhys.ApplyGroundFriction(glm::vec2(1.0f, 0.0f));
	}

	//add horizontal velocity if below max speed
	if (abs(cPhys.GetVelocity().x) < Celeste::MAX_SPEED || 
		(abs(cPhys.GetVelocity().x) >= Celeste::MAX_SPEED && (cPhys.GetVelocity().x / _celeste.direction.x) < 0.0f))
	{
		cPhys.Accelerate(glm::vec2((GLfloat)_celeste.direction.x * Celeste::ACCELERATION, 0.0f), _dt);
	}

}

void StateStanding::Enter(Celeste& _celeste)
{
	if (_celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandRight");
	}
	else if (_celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("StandLeft");
	}
	_celeste.GetLocationState() = LocationState::ON_GROUND;
	_celeste.ResetDash();
	_celeste.GetPhysicsComponent().ResetVelY();

	if (abs(_celeste.GetPhysicsComponent().GetVelocity().x) > Celeste::MAX_SPEED)
	{
		GLfloat dir = _celeste.GetPhysicsComponent().GetVelocity().x / abs(_celeste.GetPhysicsComponent().GetVelocity().x);
		_celeste.GetPhysicsComponent().SetVelX(dir * Celeste::MAX_SPEED);
	}

	//reset climb timer
	_celeste.climbTimer = 0.0f;
}