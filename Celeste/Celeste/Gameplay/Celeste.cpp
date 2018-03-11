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
	if (CheckCollision(_other))
	{
		GLfloat top = this->pos.y;
		GLfloat bot = this->pos.y + this->size.y;
		GLfloat left = this->pos.x;
		GLfloat right = this->pos.x + this->size.x;

		GLfloat otherTop = _other.pos.y;
		GLfloat otherBot = _other.pos.y + _other.size.y;
		GLfloat otherLeft = _other.pos.x;
		GLfloat otherRight = _other.pos.x + _other.size.x;

		if (top <= otherBot)
		{
			
		}

		else if (bot >= otherTop)
		{
			if (_other.GetType() == ObjectType::PLATFORM && GetState() == LocationState::IN_AIR)
			{
				delete currentState;
				currentState = new StateStanding();
				currentState->Enter(*this);
			}
		}

		else if (left <= otherRight)
		{

		}

		else if (right >= otherLeft)
		{

		}
	}

	else
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

GLfloat Celeste::GetSpeed() const
{
	return speed;
}

LocationState Celeste::GetState()
{
	return currentState->GetState();
}
