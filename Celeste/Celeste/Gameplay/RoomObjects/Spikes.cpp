#include "Spikes.h"

#include "../Celeste.h"

Spikes::Spikes() :
	GameObject()
{
	objectType = ObjectType::SPIKES;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

Spikes::Spikes(glm::vec2 _pos, glm::vec2 _size, GLfloat _rot, Texture2D _sprite, glm::vec3 _color) :
	GameObject(_pos, _size, _sprite, _color)
{
	objectType = ObjectType::SPIKES;
	rot = _rot;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

Spikes::~Spikes()
{
}

void Spikes::Update(GLfloat _dt)
{
}

void Spikes::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}