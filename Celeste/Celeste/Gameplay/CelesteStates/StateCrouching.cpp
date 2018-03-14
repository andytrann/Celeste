#include "StateCrouching.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateStanding.h"
#include "StateInAir.h"

CelesteState * StateCrouching::HandleInput(Celeste & _celeste, GLfloat _dt)
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
	if (Keyboard::KeyDown(GLFW_KEY_N))
	{
		_celeste.vel.y = -_celeste.JUMP_FORCE;
		return new StateInAir();
	}
	else
	{
		//change sprite according to new direction
		if (_celeste.direction.x == 1 && _celeste.GetFacingDirection() == 1)
		{
			_celeste.sprite = ResourceManager::GetTexture("CrouchRight");
		}
		else if (_celeste.direction.x == -1 && _celeste.GetFacingDirection() == -1)
		{
			_celeste.sprite = ResourceManager::GetTexture("CrouchLeft");
		}

		//update direction
		_celeste.direction.x = newDirection.x;
		return nullptr;
	}
}

void StateCrouching::Enter(Celeste & _celeste)
{
	_celeste.vel.x = 0.0f;

	if (_celeste.GetFacingDirection() == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchRight");
	}
	else if (_celeste.GetFacingDirection() == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchLeft");
	}
	_celeste.GetLocationState() = LocationState::ON_GROUND;
}

