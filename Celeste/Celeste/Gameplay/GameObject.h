#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../Engine/Graphics/Texture2D.h"
#include "../Engine/Graphics/SpriteRenderer.h"


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <tuple>

class PhysicsComponent;

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

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f),  glm::vec2 _vel = glm::vec2(0.0f, 0.0f));
	~GameObject();

	virtual void Update(GLfloat _dt) {}
	virtual void ResolveCollision(GameObject& _other) {}
	virtual void Render(SpriteRenderer& _renderer);
	ObjectType GetType() const;
	void CreatePhysicsComponent(glm::vec2 _TLOffset, glm::vec2 _size, GLfloat _gravity, GLfloat _maxSpeed, GLfloat _gFric, GLfloat _aFric);
	PhysicsComponent& GetPhysicsComponent();

	glm::vec2 pos, size;
	glm::vec3 color;
	GLfloat rot;
	GLboolean destroyed;
	Texture2D sprite;

protected:
	
	ObjectType objectType;
	PhysicsComponent* physics;
};

#endif
