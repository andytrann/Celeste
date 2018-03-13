#include "Celeste.h"

#include "../Engine/Engine.h"
#include "CelesteStates/StateStanding.h"
#include "CelesteStates/StateInAir.h"


const GLfloat Celeste::MAX_SPEED = 250.0f;
const GLfloat Celeste::ACCELERATION = 1000.0f;
const GLfloat Celeste::FRICTION = .4f;
const GLfloat Celeste::JUMP_FORCE = 550.0f;

Celeste::Celeste() : 
	GameObject(),
	direction(1)
{
	objectType = ObjectType::CELESTE;
}

Celeste::Celeste(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color, glm::vec2 _vel) :
	GameObject(_pos, _size, _sprite, _color, _vel),
	currentState(new StateStanding()),
	direction(1)
{
	objectType = ObjectType::CELESTE;
}

Celeste::~Celeste()
{
	delete currentState;
	currentState = nullptr;
}

void Celeste::HandleInput()
{
	CelesteState* state = currentState->HandleInput(*this, Engine::GetDT());
	if (state != nullptr)
	{
		delete currentState;
		currentState = state;

		currentState->Enter(*this);
	}
}

void Celeste::Update(GLfloat _dt)
{
	physics.Update(*this, _dt);
}

void Celeste::DoCollision(std::vector<GameObject> _other)
{
	bool inAir = true;
	for (unsigned int i = 0; i < _other.size(); i++)
	{
		Collision col = GetCollision(_other[i]);

		switch (std::get<0>(col))
		{
		case Direction::UP:
			if (_other[i].GetType() == ObjectType::PLATFORM && GetState() == LocationState::IN_AIR && vel.y > 0)
			{
				//move celeste back up difference of penetration
				GLfloat penetration = size.y / 2.0f - abs(std::get<1>(col).y);
				pos.y -= penetration;

				//change state
				delete currentState;
				currentState = new StateStanding();
				currentState->Enter(*this);
			}
			inAir = false;
			break;
		case Direction::DOWN:
			if (_other[i].GetType() == ObjectType::PLATFORM && GetState() == LocationState::IN_AIR)
			{
				//move celeste back up difference of penetration
				GLfloat penetration = size.y / 2.0f - abs(std::get<1>(col).y);
				vel.y = 0.0f;
				pos.y += penetration;
			}
			break;
		case Direction::LEFT:
			if (_other[i].GetType() == ObjectType::PLATFORM)
			{
				//move celeste back up difference of penetration
				GLfloat penetration = size.x / 2.0f - abs(std::get<1>(col).x);
				vel.x = 0.0f;
				pos.x -= penetration;
			}
			break;
		case Direction::RIGHT:
			if (_other[i].GetType() == ObjectType::PLATFORM)
			{
				//move celeste back up difference of penetration
				GLfloat penetration = size.x / 2.0f - abs(std::get<1>(col).x);
				vel.x = 0.0f;
				pos.x += penetration;
			}
			break;
		case Direction::NONE:
			break;
		default:
			break;
		}
	}
	if (inAir)
	{
		delete currentState;
		currentState = new StateInAir();
		currentState->Enter(*this);
	}
}

void Celeste::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

LocationState Celeste::GetState()
{
	return currentState->GetState();
}
