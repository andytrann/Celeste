#include "PhysicsComponent.h"

#include "Celeste.h"

float PhysicsComponent::GRAVITY = 1600.0f;
float PhysicsComponent::MAX_FALL_SPEED = 700.0f;

void PhysicsComponent::Update(Celeste& _celeste, float _dt)
{
	if (_celeste.GetLocationState() == LocationState::IN_AIR && !_celeste.isDashing)
	{
		if (_celeste.vel.y < MAX_FALL_SPEED)
		{
			_celeste.vel.y += (GRAVITY * _dt);
		}
		else
		{
			_celeste.vel.y = MAX_FALL_SPEED;
		}

		if (_celeste.vel.x > _celeste.MAX_SPEED)
		{
			_celeste.vel.x = _celeste.MAX_SPEED;
		}
		else if (_celeste.vel.x < -_celeste.MAX_SPEED)
		{
			_celeste.vel.x = -_celeste.MAX_SPEED;
		}
	}
	else if (_celeste.GetLocationState() == LocationState::ON_GROUND && !_celeste.isDashing)
	{
		_celeste.vel.y = 0;

		if (_celeste.vel.x > _celeste.MAX_SPEED)
		{
			_celeste.vel.x = _celeste.MAX_SPEED;
		}
		else if (_celeste.vel.x < -_celeste.MAX_SPEED)
		{
			_celeste.vel.x = -_celeste.MAX_SPEED;
		}
	}

	_celeste.pos += (_celeste.vel * _dt);
}