#include "Celeste.h"

#include "CelesteStates/StateStanding.h"
#include "CelesteStates/StateInAir.h"

Celeste::Celeste() : 
	GameObject(),
	speed(100.0f),
	direction(1)
{
	objectType = ObjectType::CELESTE;
}

Celeste::Celeste(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, GLfloat _speed, glm::vec3 _color, glm::vec2 _vel) :
	GameObject(_pos, _size, _sprite, _color, _vel),
	currentState(new StateStanding()),
	speed(_speed),
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
	CelesteState* state = currentState->HandleInput(*this);
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
	currentState->Update(*this, _dt);
}

void Celeste::DoCollision(GameObject& _other)
{
	Collision col = GetCollision(_other);
	
	switch (std::get<0>(col))
	{
	case Direction::UP :
		if (_other.GetType() == ObjectType::PLATFORM && GetState() == LocationState::IN_AIR)
		{
			//move celeste back up difference of penetration
			GLfloat penetration = size.y / 2.0f - abs(std::get<1>(col).y);
			pos.y -= penetration;

			//change state
			delete currentState;
			currentState = new StateStanding();
			currentState->Enter(*this);
		}
		break;
	case Direction::DOWN:
		break;
	case Direction::LEFT:
		break;
	case Direction::RIGHT:
		break;
	case Direction::NONE:
		delete currentState;
		currentState = new StateInAir();
		currentState->Enter(*this);
		break;
	default:
		break;
	}
}

void Celeste::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

GLfloat Celeste::GetSpeed() const
{
	return speed;
}

LocationState Celeste::GetState()
{
	return currentState->GetState();
}
