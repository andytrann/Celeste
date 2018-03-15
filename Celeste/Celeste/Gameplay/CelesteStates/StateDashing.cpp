#include "StateDashing.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"

#include "StateInAir.h"
#include "StateStanding.h"

CelesteState * StateDashing::HandleInput(Celeste & _celeste, GLfloat _dt)
{
	if (_celeste.dashTimer >= Celeste::DASH_CD)
	{
		_celeste.dashTimer = 0.0f;
		_celeste.isDashing = false;
		_celeste.vel.y *= .6f;
		_celeste.vel.x *= .5f;
		return new StateInAir();
	}

	_celeste.dashTimer += _dt;
	return nullptr;
}

void StateDashing::Enter(Celeste & _celeste)
{
	if (_celeste.facingDirection == 1)
	{
		_celeste.sprite = ResourceManager::GetTexture("DashRight");
	}
	else if (_celeste.facingDirection == -1)
	{
		_celeste.sprite = ResourceManager::GetTexture("DashLeft");
	}
	_celeste.isDashing = true;
}

