#ifndef PLATFORM_H
#define PLATFORM_H

#include "../GameObject.h"

class Platform : public GameObject
{
public:
	Platform();
	Platform(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f));
	~Platform();

	void Update(GLfloat _dt);
	void Render(SpriteRenderer & _renderer);

private:

};

#endif
