#include "PhysicsComponent.h"

#include "Celeste.h"

PhysicsComponent::PhysicsComponent() :
	vel(glm::vec2(0.0f, 0.0f)),
	groundFriction(.45f),
	airFriction(groundFriction * 2.0f),
	gravity(1800.0f)
{
}

void PhysicsComponent::Update(Celeste & _celeste, GLfloat _dt)
{
	//check if not dashing and is in air
	if (!_celeste.isDashing && _celeste.GetLocationState() == LocationState::IN_AIR)
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
