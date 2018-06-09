#ifndef EXIT_H
#define EXIT_H

#include "../GameObject.h"

class RoomManager;

class Exit : public GameObject
{
public:
	Exit();
	Exit(glm::vec2 _pos, glm::vec2 _translation, int _roomID, Texture2D _sprite, glm::vec3 _color = glm::vec3(1.0f));
	~Exit();

	void Update(GLfloat _dt);
	void Render(SpriteRenderer & _renderer);

	void ResolveCollision(GameObject& _other);

private:
	int roomID;
	glm::vec2 translation;
};

#endif