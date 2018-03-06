#include "GameObject.h"

GameObject::GameObject() : 
	pos(0, 0),
	size(1, 1),
	vel(0.0f),
	color(1.0f),
	rot(0.0f),
	sprite(),
	destroyed(false),
	objectType(ObjectType::NONE)
{
}

GameObject::GameObject(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color, glm::vec2 _vel) : 
	pos(_pos),
	size(_size),
	vel(_vel),
	color(_color),
	rot(0.0f),
	sprite(_sprite),
	destroyed(false),
	objectType(ObjectType::NONE)
{
}

void GameObject::Draw(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

ObjectType GameObject::GetType() const
{
	return objectType;
}