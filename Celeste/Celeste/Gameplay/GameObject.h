#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../Engine/Graphics/Texture2D.h"
#include "../Engine/Graphics/SpriteRenderer.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <tuple>

enum class ObjectType
{
	CELESTE,
	PLATFORM,
	PASSABLE_PLATFORM,
	ACCELERATOR_PLATFORM,
	SPIKES,
	STRAWBERRY,
	GEM,
	EXIT,
	NONE
};

enum class Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

typedef std::tuple<Direction, glm::vec2> Collision;

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f),  glm::vec2 _vel = glm::vec2(0.0f, 0.0f));

	virtual void Update(GLfloat _dt) {}
	virtual void DoCollision(GameObject& _other) {}
	virtual void Render(SpriteRenderer& _renderer);
	ObjectType GetType() const;

	glm::vec2 pos, size;
	glm::vec3 color;
	GLfloat rot;
	GLboolean destroyed;
	Texture2D sprite;

protected:
	GLboolean CheckCollision(GameObject& _other);
	Collision GetCollision(GameObject& _other);
	ObjectType objectType;
};

#endif
