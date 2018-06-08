#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "GameObject.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

class GameObject;
class Celeste;

class PhysicsComponent
{
public:
	PhysicsComponent(GameObject& _object, GLfloat _TLOffset, GLfloat _size, GLfloat _gravity, GLfloat _maxSpeed, GLfloat _gFric = 1.0f, GLfloat _aFric = 1.0f);
	void Update(Celeste& _celeste, GLfloat _dt);
	void Accelerate(glm::vec2 _amt, GLfloat _dt);
	
	glm::vec2 GetVelocity() const;
	void SetVelX(GLfloat _amt);
	void SetVelY(GLfloat _amt);
	void ResetVelY();
	void ResetVelX();

	void ApplyGroundFriction(glm::vec2 _dir);
	void ApplyAirFriction();

private:
	GameObject & gameObject;
	glm::vec2 pos, size;
	glm::vec2 vel;
	GLfloat groundFriction;
	GLfloat airFriction;
	float gravity;
	GLfloat maxSpeed;
};

#endif
