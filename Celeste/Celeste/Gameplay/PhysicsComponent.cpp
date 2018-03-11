#include "PhysicsComponent.h"

#include "Celeste.h"

float PhysicsComponent::GRAVITY = 400.0f;
float PhysicsComponent::MAX_FALL_SPEED = 300.0f;

void PhysicsComponent::Update(Celeste& _celeste, float _dt)
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