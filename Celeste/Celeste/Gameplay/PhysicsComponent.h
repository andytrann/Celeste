#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "GameObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <tuple>

class GameObject;
class Celeste;

enum class Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

typedef std::tuple<Direction, glm::vec2> Collision;

class PhysicsComponent
{
public:
	PhysicsComponent(GameObject& _object, glm::vec2 _TLOffset, glm::vec2 _size, GLfloat _gravity, GLfloat _maxSpeed, GLfloat _gFric = 1.0f, GLfloat _aFric = 1.0f);
	void Update(GLboolean _affByGrav, GLfloat _dt);
	void Render(SpriteRenderer& _renderer);
	void Accelerate(glm::vec2 _amt, GLfloat _dt);
	
	glm::vec2 GetPos() const;
	glm::vec2 GetSize() const;
	glm::vec2 GetLastPos() const;

	glm::vec2 GetVelocity() const;
	void SetVelX(GLfloat _amt);
	void SetVelY(GLfloat _amt);
	void ResetVelY();
	void ResetVelX();

	void ApplyGroundFriction(glm::vec2 _dir);
	void ApplyAirFriction();

	GLboolean CheckCollision(PhysicsComponent& _other);
	Collision GetCollision(PhysicsComponent& _other);

private:
	Texture2D sprite;
	GameObject & gameObject;
	glm::vec2 TLOffset, size;
	glm::vec2 vel;
	GLfloat groundFriction;
	GLfloat airFriction;
	float gravity;
	GLfloat maxSpeed;
	glm::vec2 lastPos;
};

#endif
