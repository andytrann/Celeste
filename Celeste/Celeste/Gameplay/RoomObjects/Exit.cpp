#include "Exit.h"

#include "../Celeste.h"
#include "../RoomManager.h"
#include "../../Engine/ResourceManager.h"
#include "../../Engine/Engine.h"
#include "../PhysicsComponent.h"

Exit::Exit() : 
	GameObject(),
	roomID(0),
	translation(glm::vec2(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT))
{
	objectType = ObjectType::EXIT;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

Exit::Exit(glm::vec2 _pos, glm::vec2 _translation, int _roomID, Texture2D _sprite, glm::vec3 _color) : 
	GameObject(_pos, glm::vec2(100.0f, 100.0f), _sprite, _color),
	roomID(_roomID),
	translation(_translation)
{
	objectType = ObjectType::EXIT;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 0.0f, 0.0f, 0.0f, 0.0f);
}

Exit::~Exit()
{
}

void Exit::Update(GLfloat _dt)
{
}

void Exit::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

void Exit::ResolveCollision(GameObject & _other)
{
	if (physics->CheckCollision(_other.GetPhysicsComponent()) && _other.GetType() == ObjectType::CELESTE)
	{
		RoomManager::SetCurrentRoom(roomID);
		_other.pos += translation;
	}
}
