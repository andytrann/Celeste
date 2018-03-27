#include "Celeste.h"

#include "../Engine/Engine.h"
#include "CelesteStates/StateStanding.h"
#include "CelesteStates/StateInAir.h"

#include <iostream>

GLfloat Celeste::MAX_SPEED = 300.0f;
const GLfloat Celeste::ACCELERATION = 1400.0f;
const GLfloat Celeste::FRICTION = .45f;
const GLfloat Celeste::JUMP_FORCE = 600.0f;
const GLfloat Celeste::DASH_FORCE = 500.0f;
const GLfloat Celeste::DASH_CD = .2f;
const GLfloat Celeste::MAX_CLIMB_DURATION = 10.0f;
const GLfloat Celeste::MAX_CLIMB_SPEED = 150.0f;

Celeste::Celeste() : 
	GameObject(),
	direction(glm::ivec2(1,0)),
	facingDirection(1),
	dashTimer(0.0f),
	isDashing(false),
	dashCount(1),
	wallJump(false),
	climb(false),
	climbTimer(0.0f),
	isClimbing(false)
{
	objectType = ObjectType::CELESTE;
}

Celeste::Celeste(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color, glm::vec2 _vel) :
	GameObject(_pos, _size, _sprite, _color, _vel),
	currentState(new StateStanding()),
	direction(glm::ivec2(1,0)),
	facingDirection(1),
	dashTimer(0.0f),
	isDashing(false),
	dashCount(1),
	wallJump(false),
	climb(false),
	climbTimer(0.0f),
	isClimbing(false)
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
	switch (locState)
	{
	case LocationState::ON_GROUND:
		//std::cout << "ON_GROUND" << std::endl;
		break;
	case LocationState::IN_AIR:
		//std::cout << "IN_AIR" << std::endl;
		break;
	case LocationState::CLIMBING:
		//std::cout << "CLIMBING" << std::endl;
	default:
		//std::cout << "NONE" << std::endl;
		break;
	}
	physics.Update(*this, _dt);
}

void Celeste::DoCollision(std::vector<GameObject> _other)
{
	bool inAir = true;
	bool touchingSomethingLR = false;
	for (unsigned int i = 0; i < _other.size(); i++)
	{
		Collision col = GetCollision(_other[i]);

		switch (std::get<0>(col))
		{
		case Direction::UP:
			//if dashing and collides with ground from top
			if (_other[i].GetType() == ObjectType::PLATFORM && isDashing && vel.y > 0)
			{
				GLfloat penetration = size.y / 2.0f - abs(std::get<1>(col).y);
				pos.y -= penetration;
				vel.y = 0.0f;
				locState = LocationState::ON_GROUND;
			}
			//if collides with ground normally 
			if (_other[i].GetType() == ObjectType::PLATFORM && locState == LocationState::IN_AIR && vel.y > 0)
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
			if (_other[i].GetType() == ObjectType::PLATFORM && locState == LocationState::IN_AIR)
			{
				//move celeste back down difference of penetration
				GLfloat penetration = size.y / 2.0f - abs(std::get<1>(col).y);
				vel.y = 0.0f;
				pos.y += penetration;
			}
			break;
		case Direction::LEFT:
			if (_other[i].GetType() == ObjectType::PLATFORM)
			{
				//move celeste back left difference of penetration
				GLfloat penetration = size.x / 2.0f - abs(std::get<1>(col).x);
				vel.x = 0.0f;
				pos.x -= penetration;
			}
			touchingSomethingLR = true;
			break;
		case Direction::RIGHT:
			if (_other[i].GetType() == ObjectType::PLATFORM)
			{
				//move celeste back right difference of penetration
				GLfloat penetration = size.x / 2.0f - abs(std::get<1>(col).x);
				vel.x = 0.0f;
				pos.x += penetration;
			}
			touchingSomethingLR = true;
			break;
		case Direction::NONE:
			break;
		default:
			break;
		}
	}

	//transition from end of dash to in air state
	if (inAir && !isDashing && locState != LocationState::CLIMBING)
	{
		delete currentState;
		currentState = new StateInAir();
		currentState->Enter(*this);
	}
	else if (inAir && isDashing)
	{
		locState = LocationState::IN_AIR;
	}

	//check if player can wall jump or not
	if (locState == LocationState::IN_AIR && !touchingSomethingLR || locState == LocationState::ON_GROUND)
	{
		wallJump = false;
	}
	else if (locState == LocationState::IN_AIR && touchingSomethingLR )
	{
		wallJump = true;
	}

	//check if player can wall climb or not
	if (touchingSomethingLR && climbTimer < MAX_CLIMB_DURATION)
	{
		climb = true;
	}
	else
	{
		climb = false;
	}

	if (touchingSomethingLR)
	{
		std::cout << "nnnnnn" << std::endl;
	}
	else
	{
		std::cout << "........" << std::endl;
	}
}

void Celeste::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

LocationState& Celeste::GetLocationState()
{
	return locState;
}

bool Celeste::UseDash()
{
	if (dashCount > 0)
	{
		//dashCount--;
		return true;
	}
	else
	{
		return false;
	}
}

void Celeste::ResetDash()
{
	dashCount = 1;
}

void Celeste::MaxSpeedUp()
{
	MAX_SPEED = DASH_FORCE;
}

void Celeste::MaxSpeedDown()
{
	MAX_SPEED = 300.0f;
}

GLfloat & Celeste::GetMaxSpeed() const
{
	return MAX_SPEED;
}

bool Celeste::CanWallJump() const
{
	return wallJump;
}

bool Celeste::CanClimb() const
{
	return climb && climbTimer < MAX_CLIMB_DURATION;
}
