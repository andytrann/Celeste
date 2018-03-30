#include "Gem.h"

#include "../Celeste.h"

#include <iostream>

const GLfloat Gem::COOLDOWN = 5.0f;

Gem::Gem() :
	GameObject(),
	timer(0.0f),
	active(true)
{
	objectType = ObjectType::GEM;
}

Gem::Gem(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color) :
	GameObject(_pos, _size, _sprite, _color),
	timer(0.0f),
	active(true)
{
	objectType = ObjectType::GEM;
}

Gem::~Gem()
{
}

void Gem::Update(GLfloat _dt)
{
	std::cout << active << std::endl;
	if (!active)
	{
		if (timer >= COOLDOWN)
		{
			timer = 0.0f;
			active = true;
		}
		else
		{
			timer += _dt;
		}
	}
}

void Gem::Render(SpriteRenderer & _renderer)
{
	if (active)
	{
		_renderer.DrawSprite(sprite, pos, size, rot, color);
	}
}

void Gem::DoCollision(GameObject & _other)
{
	if (CheckCollision(_other) && _other.GetType() == ObjectType::CELESTE)
	{
		active = false;
	}
}
