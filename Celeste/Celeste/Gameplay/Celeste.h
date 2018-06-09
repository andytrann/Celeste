#ifndef CELESTE_H
#define CELESTE_H

#include "GameObject.h"
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
	void ResolveCollision(std::vector<GameObject*> _other);
	void Render(SpriteRenderer& _renderer);

	LocationState& GetLocationState();

	bool UseDash();
	void ResetDash();

	bool CanWallJump() const;
	bool CanClimb() const;

	bool InputLockout();
	void StartInputLock(GLfloat _minYVel);

	void Respawn();
	
	const static GLfloat MAX_SPEED;
	const static GLfloat ACCELERATION;
	const static GLfloat FRICTION;
	const static GLfloat JUMP_FORCE;
	const static GLfloat DASH_FORCE;
	const static GLfloat DASH_CD;
	const static GLfloat MAX_FALL_SPEED;
	const static GLfloat MAX_WALL_SLIDE_SPEED;
	const static GLfloat MAX_CLIMB_DURATION;
	const static GLfloat MAX_CLIMB_SPEED_UP;
	const static GLfloat MAX_CLIMB_SPEED_DOWN;

	glm::ivec2 direction;
	int facingDirection;
	GLfloat dashTimer;
	GLboolean isDashing;
	GLfloat climbTimer;
	GLboolean isClimbing;

private:
	glm::vec2 spawnLoc;
	int dashCount;
	bool wallJump;
	bool climb;
	bool inputLocked;
	GLfloat minYVelLockout;
	LocationState locState;
	CelesteState* currentState;
	
};
#endif