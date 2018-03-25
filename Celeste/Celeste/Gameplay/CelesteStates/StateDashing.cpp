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
		//adjustment so when celeste dashes up, shes not as floaty after dash
		if(_celeste.vel.y < 0)
		{
			_celeste.vel.y *= .8f;
		}
		return new StateInAir();
	}

	if (Keyboard::KeyDown(GLFW_KEY_N) && _celeste.GetLocationState() == LocationState::ON_GROUND)
	{
		_celeste.dashTimer = 0.0f;
		_celeste.isDashing = false;
		//adjustment so when celeste dashes up, shes not as floaty after dash
		if (_celeste.vel.y < 0)
		{
			_celeste.vel.y *= .8f;
		}

		//change max speed so dash carries you through air
		_celeste.MaxSpeedUp();
		_celeste.vel.y -= _celeste.JUMP_FORCE;
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

