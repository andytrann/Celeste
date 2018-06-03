#include "StateCrouching.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateStanding.h"
#include "StateInAir.h"
#include "StateDashing.h"

CelesteState * StateCrouching::HandleInput(Celeste & _celeste)
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
	if (Keyboard::KeyUp(GLFW_KEY_S))
	{
		return new StateStanding();
	}
	newDirection.y = 1;

	//update direction
	_celeste.direction.x = newDirection.x;
	_celeste.direction.y = newDirection.y;

	//change sprite according to new direction
	if (_celeste.direction.x == 1 && _celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchRight");
		_celeste.facingDirection = 1;
	}
	else if (_celeste.direction.x == -1 && _celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchLeft");
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
		//if holding down and left/right
		if (newDirection.x != 0 && newDirection.y != 0)
		{
			cPhys.Accelerate((glm::vec2)newDirection * glm::sin(glm::quarter_pi<GLfloat>()) * Celeste::DASH_FORCE, 1.0f);
			return new StateDashing();
		}
		//if only holding down
		else
		{
			cPhys.Accelerate((glm::vec2)newDirection * Celeste::DASH_FORCE, 1.0f);
			return new StateDashing();
		}
	}
	
	return nullptr;
}

void StateCrouching::Update(Celeste & _celeste, GLfloat _dt)
{
	_celeste.GetPhysicsComponent().ApplyGroundFriction(glm::vec2(1.0f, 0.0f));
}

void StateCrouching::Enter(Celeste & _celeste)
{
	if (_celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchRight");
	}
	else if (_celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchLeft");
	}
	_celeste.GetLocationState() = LocationState::ON_GROUND;
}

