#include "Gem.h"

#include "../Celeste.h"
#include "../../Engine/ResourceManager.h"
#include "../PhysicsComponent.h"

const GLfloat Gem::COOLDOWN = 3.0f;

Gem::Gem() :
	GameObject(),
	timer(0.0f),
	spriteOutline(ResourceManager::GetTexture("GemOutline"))
{
	objectType = ObjectType::GEM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

Gem::Gem(glm::vec2 _pos, Texture2D _sprite, glm::vec3 _color) :
	GameObject(_pos, glm::vec2(30.0f, 30.0f), _sprite, _color),
	timer(0.0f),
	spriteOutline(ResourceManager::GetTexture("GemOutline"))
{
	objectType = ObjectType::GEM;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
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

void Gem::ResolveCollision(GameObject & _other)
{
	if (physics->CheckCollision(_other.GetPhysicsComponent()) && _other.GetType() == ObjectType::CELESTE)
	{
		destroyed = true;
	}
}
