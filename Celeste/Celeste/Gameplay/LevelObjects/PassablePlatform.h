#ifndef PASSABLE_PLATFORM_H
#define PASSABLE_PLATFORM_H

#include "../GameObject.h"

class PassablePlatform : public GameObject
{
public:
	PassablePlatform();
	PassablePlatform(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f));
	~PassablePlatform();

	void Update(GLfloat _dt);
	void Render(SpriteRenderer & _renderer);

private:

};

#endif
