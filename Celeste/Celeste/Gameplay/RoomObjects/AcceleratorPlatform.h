#ifndef ACCELERATOR_PLATFORM_H
#define ACCELERATOR_PLATFORM_H

#include "../GameObject.h"

class AcceleratorPlatform : public GameObject
{
public:
	AcceleratorPlatform();
	AcceleratorPlatform(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _endPos, Texture2D _sprite, Texture2D _chain, glm::vec3 _color = glm::vec3(1.0f));
	~AcceleratorPlatform();

	void Update(GLfloat _dt);
	void ResolveCollision(GameObject& _other);
	void Render(SpriteRenderer & _renderer);

	void Start();

	const static GLfloat MAX_SPEED;
	const static GLfloat ACCELERATION;
	const static GLfloat MAX_REVERSE_SPEED;
	const static GLfloat REVERSE_ACCELERATION;
	const static GLfloat STOP_BUFFER;

private:
	glm::vec2 startPos;
	glm::vec2 endPos;
	glm::vec2 dir;
	glm::vec2 vel;
	GLboolean start;
	GLfloat stopTimer;
	Texture2D chain;

};

#endif
