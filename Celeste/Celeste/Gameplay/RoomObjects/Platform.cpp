#include "Platform.h"

#include "../Celeste.h"
#include "../PhysicsComponent.h"

Platform::Platform() : 
	GameObject()
{
	objectType = ObjectType::PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

Platform::Platform(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color) : 
	GameObject(_pos, _size, _sprite, _color)
{
	objectType = ObjectType::PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

Platform::~Platform()
{
}

void Platform::Update(GLfloat _dt)
{
}

void Platform::ResolveCollision(GameObject & _other)
{
	PhysicsComponent& _otherPhys = _other.GetPhysicsComponent();
	Collision col = _otherPhys.GetCollision(*physics);
	switch (std::get<0>(col))
	{
		//_other collides from top side
		case Direction::UP:
		{
			//move _other back up difference of penetration
			GLfloat penetration = _otherPhys.GetSize().y / 2.0f - abs(std::get<1>(col).y);
			_otherPhys.ResetVelY();
			_other.pos.y -= penetration;
			break;
		}

		case Direction::DOWN:
		{
			//move _other back down difference of penetration
			GLfloat penetration = _otherPhys.GetSize().y / 2.0f - abs(std::get<1>(col).y);
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
			break;
		}

		case Direction::RIGHT:
		{
			//move _other back right difference of penetration
			GLfloat penetration = _otherPhys.GetSize().x / 2.0f - abs(std::get<1>(col).x);
			_otherPhys.ResetVelX();
			_other.pos.x += penetration;
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

void Platform::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}
