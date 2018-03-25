#include "PhysicsComponent.h"

#include "Celeste.h"

float PhysicsComponent::GRAVITY = 1800.0f;
float PhysicsComponent::MAX_FALL_SPEED = 600.0f;

void PhysicsComponent::Update(Celeste& _celeste, float _dt)
{
	//check for wall slide
	if (_celeste.direction.x != 0 && _celeste.CanWallJump())
	{
		MaxFallSpeedDown();
	}
	else
	{
		MaxFallSpeedUp();
	}

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

		if (_celeste.vel.x > _celeste.GetMaxSpeed())
		{
			_celeste.vel.x = _celeste.GetMaxSpeed();
		}
		else if (_celeste.vel.x < -_celeste.GetMaxSpeed())
		{
			_celeste.vel.x = -_celeste.GetMaxSpeed();
		}
	}
	else if (_celeste.GetLocationState() == LocationState::ON_GROUND && !_celeste.isDashing)
	{
		_celeste.vel.y = 0;

		if (_celeste.vel.x > _celeste.GetMaxSpeed())
		{
			_celeste.vel.x = _celeste.GetMaxSpeed();
		}
		else if (_celeste.vel.x < -_celeste.GetMaxSpeed())
		{
			_celeste.vel.x = -_celeste.GetMaxSpeed();
		}
	}

	_celeste.pos += (_celeste.vel * _dt);
}

void PhysicsComponent::MaxFallSpeedDown()
{
	MAX_FALL_SPEED = 200.0f;
}

void PhysicsComponent::MaxFallSpeedUp()
{
	MAX_FALL_SPEED = 600.0f;
}
