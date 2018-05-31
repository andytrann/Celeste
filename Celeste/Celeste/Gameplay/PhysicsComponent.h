#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class GameObject;

class PhysicsComponent
{
public:
	PhysicsComponent();
	//void Update(Celeste& _celeste, float _dt);
	void Update(GameObject& _object, GLfloat _dt);
	void Accelerate(glm::vec2 _amt, GLfloat _dt);
	
	glm::vec2 GetVelocity() const;
	void ResetVelY();
	void ResetVelX();

	void ApplyFriction();

private:
	glm::vec2 vel;
	GLfloat friction;
	float gravity;
};

#endif
