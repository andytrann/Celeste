#include "Platform.h"

Platform::Platform() : 
	GameObject()
{
	objectType = ObjectType::PLATFORM;
}

Platform::Platform(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color) : 
	GameObject(_pos, _size, _sprite, _color)
{
	objectType = ObjectType::PLATFORM;
}

Platform::~Platform()
{
}

void Platform::Update(GLfloat _dt)
{
}

void Platform::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}
