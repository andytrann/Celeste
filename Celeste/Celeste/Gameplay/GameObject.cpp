#include "GameObject.h"

#include "PhysicsComponent.h"

GameObject::GameObject() : 
	pos(0, 0),
	size(1, 1),
	color(1.0f),
	rot(0.0f),
	sprite(),
	destroyed(false),
	objectType(ObjectType::NONE)
{
	physics = nullptr;
}

GameObject::GameObject(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color, glm::vec2 _vel) : 
	pos(_pos),
	size(_size),
	color(_color),
	rot(0.0f),
	sprite(_sprite),
	destroyed(false),
	objectType(ObjectType::NONE)
{
	physics = nullptr;
}

GameObject::~GameObject()
{
	delete physics;
	physics = nullptr;
}

void GameObject::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

ObjectType GameObject::GetType() const
{
	return objectType;
}

void GameObject::CreatePhysicsComponent(glm::vec2 _TLOffset, glm::vec2 _size, GLfloat _gravity, GLfloat _maxSpeed, GLfloat _gFric, GLfloat _aFric)
{
	if (physics == nullptr)
	{
		physics = new PhysicsComponent(*this, _TLOffset, _size, _gravity, _maxSpeed, _gFric, _aFric);
	}
}

PhysicsComponent & GameObject::GetPhysicsComponent()
{
	return *physics;
}