#include "Gem.h"

#include "../Celeste.h"

Gem::Gem() :
	GameObject()
{
	objectType = ObjectType::GEM;
}

Gem::Gem(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color) :
	GameObject(_pos, _size, _sprite, _color)
{
	objectType = ObjectType::GEM;
}

Gem::~Gem()
{
}

void Gem::Update(GLfloat _dt)
{
}

void Gem::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}
