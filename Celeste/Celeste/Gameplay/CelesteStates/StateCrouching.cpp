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

	if (Keyboard::KeyDown(GLFW_KEY_N))
	{
		_celeste.vel.y = -_celeste.JUMP_FORCE;
		return new StateInAir();
	}
	if (Keyboard::KeyDown(GLFW_KEY_M) && _celeste.UseDash())
	{
		
		//if holding down and left/right
		if (newDirection.x != 0 && newDirection.y != 0)
		{
			_celeste.vel = (glm::vec2)newDirection * glm::sin(glm::quarter_pi<GLfloat>()) * Celeste::DASH_FORCE;
			return new StateDashing();
		}
		//if only holding down
		else
		{
			_celeste.vel.y = (GLfloat)newDirection.y * Celeste::DASH_FORCE;
			return new StateDashing();
		}
	}

	return nullptr;
}

void StateCrouching::Update(Celeste & _celeste, GLfloat _dt)
{
}

void StateCrouching::Enter(Celeste & _celeste)
{
	_celeste.vel.x = 0.0f;

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

