#ifndef SPIKES_H
#define SPIKES_H

#include "../GameObject.h"

class Spikes : public GameObject
{
public:
	Spikes();
	Spikes(glm::vec2 _pos, glm::vec2 _size, GLfloat _rot, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f));
	~Spikes();

	void Update(GLfloat _dt);
	void Render(SpriteRenderer & _renderer);

private:

};

#endif
