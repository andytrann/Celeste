#include "PassablePlatform.h"

#include "../Celeste.h"
#include "../PhysicsComponent.h"

PassablePlatform::PassablePlatform() :
	GameObject()
{
	objectType = ObjectType::PASSABLE_PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), glm::vec2(size.x, 30.0f), 0.0f, 0.0f, 0.0f, 0.0f);
}

PassablePlatform::PassablePlatform(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color) :
	GameObject(_pos, _size, _sprite, _color)
{
	objectType = ObjectType::PASSABLE_PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), glm::vec2(size.x, 30.0f), 0.0f, 0.0f, 0.0f, 0.0f);
}

PassablePlatform::~PassablePlatform()
{
}

void PassablePlatform::Update(GLfloat _dt)
{
}

void PassablePlatform::ResolveCollision(GameObject & _other)
{
	//need to eventually fix. if celeste comes from the bottom and the bottom of her bounding box is in between pos and pos+15 of passable platform,
	//then itll calculate penetration and push her up a bit
	PhysicsComponent& _otherPhys = _other.GetPhysicsComponent();
	Collision col = _otherPhys.GetCollision(*physics);
	if (std::get<0>(col) == Direction::UP && _otherPhys.GetPos().y + _otherPhys.GetSize().y <= physics->GetPos().y + (physics->GetSize().y / 2.0f))
	{
		GLfloat penetration = _otherPhys.GetSize().y / 2.0f - abs(std::get<1>(col).y);
		if (_otherPhys.GetVelocity().y > 0)
		{
			_otherPhys.ResetVelY();
		}
		_other.pos.y -= penetration;
		
	}
}

void PassablePlatform::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}