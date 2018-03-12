#include "StateCrouching.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"
#include "StateStanding.h"

CelesteState * StateCrouching::HandleInput(Celeste & _celeste)
{
	if (Keyboard::KeyUp(GLFW_KEY_S))
	{
		return new StateStanding();
	}
	else
	{
		return nullptr;
	}
}

void StateCrouching::Update(Celeste & _celeste, GLfloat _dt)
{
	_celeste.vel.y = 0.0f;
	_celeste.pos += (_celeste.vel * _dt);
}

void StateCrouching::Enter(Celeste & _celeste)
{
	_celeste.vel.x = 0.0f;

	if (_celeste.direction == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchRight");
	}
	else if (_celeste.direction == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("CrouchLeft");
	}
}

LocationState StateCrouching::GetState()
{
	return LocationState::ON_GROUND;
}
