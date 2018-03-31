#include "Gem.h"

#include "../Celeste.h"
#include "../../Engine/ResourceManager.h"

const GLfloat Gem::COOLDOWN = 3.0f;

Gem::Gem() :
	GameObject(),
	timer(0.0f),
	spriteOutline(ResourceManager::GetTexture("GemOutline"))
{
	objectType = ObjectType::GEM;
}

Gem::Gem(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color) :
	GameObject(_pos, _size, _sprite, _color),
	timer(0.0f),
	spriteOutline(ResourceManager::GetTexture("GemOutline"))
{
	objectType = ObjectType::GEM;
}

Gem::~Gem()
{
}

void Gem::Update(GLfloat _dt)
{
	if (destroyed)
	{
		if (timer >= COOLDOWN)
		{
			timer = 0.0f;
			destroyed = false;
		}
		else
		{
			timer += _dt;
		}
	}
}

void Gem::Render(SpriteRenderer & _renderer)
{
	if (!destroyed)
	{
		_renderer.DrawSprite(sprite, pos, size, rot, color);
	}
	else
	{
		_renderer.DrawSprite(spriteOutline, pos, size, rot, color);

	}
}

void Gem::DoCollision(GameObject & _other)
{
	if (CheckCollision(_other) && _other.GetType() == ObjectType::CELESTE)
	{
		destroyed = true;
	}
}
