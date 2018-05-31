#include "PhysicsComponent.h"

#include "Celeste.h"

//float PhysicsComponent::GRAVITY = 1800.0f;
//float PhysicsComponent::MAX_FALL_SPEED = 600.0f;

PhysicsComponent::PhysicsComponent() :
	vel(glm::vec2(0.0f, 0.0f)),
	groundFriction(.45f),
	airFriction(groundFriction * 2.0f),
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

void PhysicsComponent::Update(Celeste & _celeste, GLfloat _dt)
{
	if (_celeste.GetLocationState() == LocationState::IN_AIR && !_celeste.isDashing)
	{
		if (vel.y < Celeste::MAX_FALL_SPEED)
		{
			Accelerate(glm::vec2(0.0f, gravity), _dt);
		}
	}
	_celeste.pos += (vel * _dt);
}

void PhysicsComponent::Accelerate(glm::vec2 _amt, GLfloat _dt)
{
	vel += (_amt * _dt);
}

glm::vec2 PhysicsComponent::GetVelocity() const
{
	return vel;
}

void PhysicsComponent::SetVelX(GLfloat _amt)
{
	vel.x = _amt;
}

void PhysicsComponent::SetVelY(GLfloat _amt)
{
	vel.y = _amt;
}

void PhysicsComponent::ResetVelY()
{
	vel.y = 0.0f;
}

void PhysicsComponent::ResetVelX()
{
	vel.x = 0.0f;
}

void PhysicsComponent::ApplyGroundFriction(glm::vec2 _dir)
{
	vel *= (_dir * groundFriction);
}

void PhysicsComponent::ApplyAirFriction()
{
	vel.x *= airFriction;
}
