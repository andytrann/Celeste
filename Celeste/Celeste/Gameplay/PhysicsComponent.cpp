#include "PhysicsComponent.h"

#include "Celeste.h"

float PhysicsComponent::GRAVITY = 1600.0f;
float PhysicsComponent::MAX_FALL_SPEED = 700.0f;

void PhysicsComponent::Update(Celeste& _celeste, float _dt)
{
	if (_celeste.GetState() == LocationState::IN_AIR)
	{
		if (_celeste.vel.y < MAX_FALL_SPEED)
		{
			_celeste.vel.y += (GRAVITY * _dt);
		}
		else
		{
			_celeste.vel.y = MAX_FALL_SPEED;
		}
	}
	else if (_celeste.GetState() == LocationState::ON_GROUND)
	{
		_celeste.vel.y = 0;
	}

	_celeste.pos += (_celeste.vel * _dt);
}