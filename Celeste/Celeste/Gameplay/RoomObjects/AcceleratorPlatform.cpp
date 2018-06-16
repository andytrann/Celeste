#include "AcceleratorPlatform.h"

#include "../PhysicsComponent.h"

const GLfloat AcceleratorPlatform::MAX_SPEED = 600.0f;
const GLfloat AcceleratorPlatform::ACCELERATION = 500.0f;
const GLfloat AcceleratorPlatform::MAX_REVERSE_SPEED = 300.0f;
const GLfloat AcceleratorPlatform::REVERSE_ACCELERATION = 1000.0f;

AcceleratorPlatform::AcceleratorPlatform() : 
	GameObject(),
	endPos(glm::vec2(0.0f, 0.0f)),
	dir(glm::vec2(0.0f, 0.0f)),
	start(false),
	chain()
{
	objectType = ObjectType::ACCELERATOR_PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

AcceleratorPlatform::AcceleratorPlatform(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _endPos, Texture2D _sprite, Texture2D _chain, glm::vec3 _color) : 
	GameObject(_pos, _size, _sprite),
	endPos(_endPos),
	start(false),
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

void AcceleratorPlatform::Render(SpriteRenderer & _renderer)
{
	GLfloat chainWidth = 8.0f;
	GLfloat chainLength = abs(endPos.y - pos.y);
	glm::vec2 chainEnd = endPos + (size / 2.0f) - (chainWidth / 2.0f);
	_renderer.DrawSprite(chain, chainEnd, glm::vec2(chainWidth, chainLength));
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

void AcceleratorPlatform::Start()
{
	start = true;
}
