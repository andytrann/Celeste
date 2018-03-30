#ifndef GEM_H
#define GEM_H

#include "../GameObject.h"

class Gem : public GameObject
{
public:
	Gem();
	Gem(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f));
	~Gem();

	void Update(GLfloat _dt);
	void Render(SpriteRenderer & _renderer);

	void DoCollision(GameObject& _other);

private:
	const static GLfloat COOLDOWN;

	GLfloat timer;
	bool active;
};

#endif
