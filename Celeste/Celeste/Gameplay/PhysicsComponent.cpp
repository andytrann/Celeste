#include "PhysicsComponent.h"

#include "Celeste.h"

//float PhysicsComponent::GRAVITY = 1800.0f;
//float PhysicsComponent::MAX_FALL_SPEED = 600.0f;

PhysicsComponent::PhysicsComponent() : 
	gravity(1800.0f),
	maxFallSpeed(600.0f)
{
}

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
		if (_celeste.vel.y < maxFallSpeed)
		{
			_celeste.vel.y += (gravity * _dt);
		}
		else
		{
			_celeste.vel.y = maxFallSpeed;
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
	maxFallSpeed = 200.0f;
}

void PhysicsComponent::MaxFallSpeedUp()
{
	maxFallSpeed = 600.0f;
}
