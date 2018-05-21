#ifndef ROOM_H
#define ROOM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

class GameObject;
class SpriteRenderer;
class Celeste;

class Room
{
public:
	Room();
	~Room();

	void Update(GLfloat _dt);
	void Render(SpriteRenderer& _renderer);
	void DoCollisions(Celeste& _celeste);
	void Init(std::string filePath);
	void AddObject(std::string line);

	std::vector<GameObject*> GetRoomObjects() const;
private:
	int id;
	std::vector<int> neighbors;
	std::vector<GameObject*> roomObjects;
};

#endif
