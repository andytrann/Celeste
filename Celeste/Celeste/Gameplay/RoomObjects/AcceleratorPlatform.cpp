#include "AcceleratorPlatform.h"

#include "../PhysicsComponent.h"
#include "../../Engine/IO/Keyboard.h"
#include <iostream>

const GLfloat AcceleratorPlatform::MAX_SPEED = 600.0f;
const GLfloat AcceleratorPlatform::ACCELERATION = 600.0f;
const GLfloat AcceleratorPlatform::MAX_REVERSE_SPEED = 100.0f;
const GLfloat AcceleratorPlatform::REVERSE_ACCELERATION = 300.0f;
const GLfloat AcceleratorPlatform::STOP_BUFFER = .2f;

AcceleratorPlatform::AcceleratorPlatform() : 
	GameObject(),
	startPos(glm::vec2(0.0f, 0.0f)),
	endPos(glm::vec2(0.0f, 0.0f)),
	dir(glm::vec2(0.0f, 0.0f)),
	start(false),
	stopTimer(0.0f),
	chain()
{
	objectType = ObjectType::ACCELERATOR_PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

AcceleratorPlatform::AcceleratorPlatform(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _endPos, Texture2D _sprite, Texture2D _chain, glm::vec3 _color) : 
	GameObject(_pos, _size, _sprite),
	startPos(_pos),
	endPos(_endPos),
	start(false),
	stopTimer(0.0f),
	chain(_chain)
{
	objectType = ObjectType::ACCELERATOR_PLATFORM;
	dir = glm::normalize(glm::vec2(_endPos - _pos));
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), _size, 0.0f, 0.0f, 0.0f, 0.0f);
}

AcceleratorPlatform::~AcceleratorPlatform()
{
}

void AcceleratorPlatform::Update(GLfloat _dt)
{
	if (start) 
	{
		GLfloat maxDist = glm::distance(endPos, startPos);
		GLfloat curDist = glm::distance(pos, startPos);
		if (curDist < maxDist)
		{
			stopTimer += _dt;
			if (glm::length(physics->GetVelocity()) < MAX_SPEED && stopTimer >= STOP_BUFFER)
			{
				physics->Accelerate(dir * ACCELERATION, _dt);
			}
		}
		else
		{
			//pos = endPos;
			physics->ResetVelX();
			physics->ResetVelY();
			start = false;
			stopTimer = 0.0f;
		}
	}
	else
	{
		GLfloat maxDist = glm::distance(startPos, endPos);
		GLfloat curDist = glm::distance(pos, endPos);
		if (curDist < maxDist)
		{
			stopTimer += _dt;
			if (glm::length(physics->GetVelocity()) < MAX_REVERSE_SPEED && stopTimer >= STOP_BUFFER * 2.0f)
			{
				physics->Accelerate(-dir * REVERSE_ACCELERATION, _dt);
			}
		}
		else
		{
			pos = startPos;
			physics->ResetVelX();
			physics->ResetVelY();
			stopTimer = 0.0f;
		}
	}
	physics->Update(false, _dt);
}

void AcceleratorPlatform::ResolveCollision(GameObject & _other)
{
	PhysicsComponent& _otherPhys = _other.GetPhysicsComponent();
	Collision col = _otherPhys.GetCollision(*physics);
	switch (std::get<0>(col))
	{
		//_other collides from top side
		case Direction::UP:
		{
			//move _other back up difference of penetration
			GLfloat penetration = (_otherPhys.GetSize().y / 2.0f - abs(std::get<1>(col).y));
			//should probably eventually fix. helps so celeste will stay on top of accelerator when its moving down
			if (physics->GetVelocity().y > 0)
			{
				_other.GetPhysicsComponent().GetVelocity().y = physics->GetVelocity().y + 20.0f;
			}
			_other.pos.y -= penetration;
			if (pos == startPos)
			{
				start = true;
			}
			break;
		}

		case Direction::DOWN:
		{
			//move _other back down difference of penetration
			GLfloat penetration = (_otherPhys.GetSize().y / 2.0f - abs(std::get<1>(col).y));
			_otherPhys.ResetVelY();
			_other.pos.y += penetration;
			break;
		}

		case Direction::LEFT:
		{
			//move _other back left difference of penetration
			GLfloat penetration = _otherPhys.GetSize().x / 2.0f - abs(std::get<1>(col).x);
			_otherPhys.ResetVelX();
			_other.pos.x -= penetration;
			if (pos == startPos && Keyboard::Key(GLFW_KEY_COMMA))
			{
				start = true;
			}
			break;
		}

		case Direction::RIGHT:
		{
			//move _other back right difference of penetration
			GLfloat penetration = _otherPhys.GetSize().x / 2.0f - abs(std::get<1>(col).x);
			_otherPhys.ResetVelX();
			_other.pos.x += penetration;
			if (pos == startPos && Keyboard::Key(GLFW_KEY_COMMA))
			{
				start = true;
			}
			break;
		}

		case Direction::NONE:
		{
			break;
		}

		default:
		{
			break;
		}
	}
}

void AcceleratorPlatform::Render(SpriteRenderer & _renderer)
{
	GLfloat chainWidth = 8.0f;
	GLfloat chainLength = abs(endPos.y - startPos.y);
	glm::vec2 chainEnd = endPos + (size / 2.0f) - (chainWidth / 2.0f);
	_renderer.DrawSprite(chain, chainEnd, glm::vec2(chainWidth, chainLength));
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

void AcceleratorPlatform::Start()
{
	start = true;
}
