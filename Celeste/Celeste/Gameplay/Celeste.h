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

	GLfloat GetSpeed() const;
	GLfloat GetJump() const;
	LocationState GetState();

	int direction;
private:
	CelesteState* currentState;
	PhysicsComponent physics;
	GLfloat speed;
	GLfloat jump;
};
#endif