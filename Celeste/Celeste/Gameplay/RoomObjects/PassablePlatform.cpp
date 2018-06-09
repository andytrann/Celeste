#include "PassablePlatform.h"

#include "../Celeste.h"

PassablePlatform::PassablePlatform() :
	GameObject()
{
	objectType = ObjectType::PASSABLE_PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

PassablePlatform::PassablePlatform(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color) :
	GameObject(_pos, _size, _sprite, _color)
{
	objectType = ObjectType::PASSABLE_PLATFORM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

PassablePlatform::~PassablePlatform()
{
}

void PassablePlatform::Update(GLfloat _dt)
{
}

void PassablePlatform::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}