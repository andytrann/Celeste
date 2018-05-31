#include "PhysicsComponent.h"

#include "Celeste.h"

//float PhysicsComponent::GRAVITY = 1800.0f;
//float PhysicsComponent::MAX_FALL_SPEED = 600.0f;

PhysicsComponent::PhysicsComponent() :
	vel(glm::vec2(0.0f, 0.0f)),
	friction(.45f),
	gravity(1800.0f)
{
}

/*
void PhysicsComponent::Update(Celeste& _celeste, float _dt)
{
	//check for wall slide
	if (_celeste.direction.x != 0 && _celeste.CanWallJump() && _celeste.vel.y > 0.0f)
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
		_celeste.vel.y = 0.0f;

		if (_celeste.vel.x > _celeste.GetMaxSpeed())
		{
			_celeste.vel.x = _celeste.GetMaxSpeed();
		}
		else if (_celeste.vel.x < -_celeste.GetMaxSpeed())
		{
			_celeste.vel.x = -_celeste.GetMaxSpeed();
		}
	}

	else if (_celeste.GetLocationState() == LocationState::CLIMBING)
	{
		_celeste.vel.x = 0.0f;

		if (_celeste.vel.y < climbUpSpeed)
		{
			_celeste.vel.y = climbUpSpeed;
		}
		else if (_celeste.vel.y > climbDownSpeed)
		{
			_celeste.vel.y = climbDownSpeed;
		}
	}

	_celeste.pos += (_celeste.vel * _dt);
}*/

void PhysicsComponent::Update(GameObject & _object, GLfloat _dt)
{
	_object.pos += (vel * _dt);
}

void PhysicsComponent::Accelerate(glm::vec2 _amt, GLfloat _dt)
{
	vel += (_amt * _dt);
}

glm::vec2 PhysicsComponent::GetVelocity() const
{
	return vel;
}

void PhysicsComponent::ResetVelY()
{
	vel.y = 0.0f;
}

void PhysicsComponent::ResetVelX()
{
	vel.x = 0.0f;
}

void PhysicsComponent::ApplyFriction()
{
	vel.x *= friction;
}
