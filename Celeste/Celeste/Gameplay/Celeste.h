#ifndef CELESTE_H
#define CELESTE_H

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "CelesteStates/CelesteState.h"
#include <vector>

class Celeste : public GameObject
{
public:
	Celeste();
	Celeste(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f), glm::vec2 _vel = glm::vec2(0.0f, 0.0f));
	~Celeste();

	void HandleInput();
	void Update(GLfloat _dt);
	void DoCollision(std::vector<GameObject> _other);
	void Render(SpriteRenderer& _renderer);

	LocationState& GetLocationState();
	int GetFacingDirection() const;

	const static GLfloat MAX_SPEED;
	const static GLfloat ACCELERATION;
	const static GLfloat FRICTION;
	const static GLfloat JUMP_FORCE;
	const static GLfloat DASH_FORCE;
	const static GLfloat DASH_CD;
	glm::ivec2 direction;
	GLfloat dashTimer;
	GLboolean isDashing;
private:
	int facingDirection;
	LocationState locState;

	CelesteState* currentState;
	PhysicsComponent physics;
};
#endif