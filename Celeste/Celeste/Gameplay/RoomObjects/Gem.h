#ifndef GEM_H
#define GEM_H

#include "../GameObject.h"

class Gem : public GameObject
{
public:
	Gem();
	Gem(glm::vec2 _pos, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f));
	~Gem();

	void Update(GLfloat _dt);
	void Render(SpriteRenderer & _renderer);

	void ResolveCollision(GameObject& _other);

private:
	const static GLfloat COOLDOWN;
	Texture2D spriteOutline;
	GLfloat timer;
};

#endif
