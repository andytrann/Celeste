#include "PhysicsComponent.h"

#include "Celeste.h"
#include "../Engine/ResourceManager.h"

PhysicsComponent::PhysicsComponent(GameObject & _object, glm::vec2 _TLOffset, glm::vec2 _size, GLfloat _gravity, GLfloat _maxSpeed, GLfloat _gFric, GLfloat _aFric) : 
	gameObject(_object),
	TLOffset(_TLOffset),
	vel(glm::vec2(0.0f, 0.0f)),
	size(_size),
	gravity(_gravity),
	maxSpeed(_maxSpeed),
	groundFriction(_gFric),
	airFriction(_aFric)
{
	sprite = ResourceManager::GetTexture("Exit");
}

void PhysicsComponent::Update(GLboolean _affByGrav, GLfloat _dt)
{
	if (vel.y < maxSpeed && _affByGrav)
	{
		Accelerate(glm::vec2(0.0f, gravity), _dt);
	}
	gameObject.pos += (vel * _dt);
}

void PhysicsComponent::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, gameObject.pos + TLOffset, size, gameObject.rot);
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
