#include "Celeste.h"

#include "../Engine/Engine.h"
#include "../Engine/IO/Keyboard.h"
#include "CelesteStates/StateStanding.h"
#include "CelesteStates/StateInAir.h"
#include "PhysicsComponent.h"

#include <iostream>

const GLfloat Celeste::MAX_SPEED = 300.0f;
const GLfloat Celeste::ACCELERATION = 1400.0f;
const GLfloat Celeste::FRICTION = .45f;
const GLfloat Celeste::JUMP_FORCE = 600.0f;
const GLfloat Celeste::DASH_FORCE = 500.0f;
const GLfloat Celeste::DASH_CD = .2f;
const GLfloat Celeste::MAX_FALL_SPEED = 600.0f;
const GLfloat Celeste::MAX_WALL_SLIDE_SPEED = 200.0f;
const GLfloat Celeste::MAX_CLIMB_DURATION = 10.0f;
const GLfloat Celeste::MAX_CLIMB_SPEED_UP = -200.0f;
const GLfloat Celeste::MAX_CLIMB_SPEED_DOWN = 300.0f;

Celeste::Celeste() :
	GameObject(),
	direction(glm::ivec2(1, 0)),
	facingDirection(1),
	spawnLoc(glm::vec2(0.0f, 0.0f)),
	dashTimer(0.0f),
	isDashing(false),
	dashCount(1),
	wallJump(false),
	climb(false),
	climbTimer(0.0f),
	isClimbing(false),
	inputLocked(false),
	lockoutTimer(0.0f)
{
	objectType = ObjectType::CELESTE;
	CreatePhysicsComponent(glm::vec2(0.0f, 0.0f), size, 1800.0f, MAX_FALL_SPEED, FRICTION, FRICTION * 2.0f);
}

Celeste::Celeste(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color, glm::vec2 _vel) :
	GameObject(_pos, _size, _sprite, _color, _vel),
	currentState(new StateStanding()),
	direction(glm::ivec2(1,0)),
	facingDirection(1),
	spawnLoc(_pos),
	dashTimer(0.0f),
	isDashing(false),
	dashCount(1),
	wallJump(false),
	climb(false),
	climbTimer(0.0f),
	isClimbing(false),
	inputLocked(false),
	lockoutTimer(0.0f)
{
	objectType = ObjectType::CELESTE;
	CreatePhysicsComponent(glm::vec2(0.0f, 0), size, 1800.0f, MAX_FALL_SPEED, FRICTION, FRICTION * 2.0f);
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
	currentState->Update(*this, _dt);
	InputLockoutUpdate(_dt);
	//check if not dashing and is in air
	if (!isDashing && GetLocationState() == LocationState::IN_AIR)
	{
		//apply wall slide
		if (direction.x != 0 && CanWallJump() && physics->GetVelocity().y > MAX_WALL_SLIDE_SPEED)
		{
				physics->Accelerate(glm::vec2(0.0f, -4000.0f), _dt);
		}
		//update with gravity
		physics->Update(true, _dt);
	}
	else
	{
		//update without gravity
		physics->Update(false, _dt);
	}
	
}

void Celeste::ResolveCollision(std::vector<GameObject*> _other)
{
	bool inAir = true;
	bool touchingSomethingLR = false;
	for (unsigned int i = 0; i < _other.size(); i++)
	{
		Collision col = physics->GetCollision(_other[i]->GetPhysicsComponent());
		switch (_other[i]->GetType())
		{
			case ObjectType::GEM:
			{
				if (std::get<0>(col) != Direction::NONE && !_other[i]->destroyed)
				{
					ResetDash();
				}
				break;
			}

			case ObjectType::SPIKES:
			{
				if (std::get<0>(col) != Direction::NONE)
				{
					Respawn();
				}
				break;
			}

			case ObjectType::PASSABLE_PLATFORM:
			{
				
				if (std::get<0>(col) == Direction::UP && physics->GetPos().y + physics->GetSize().y <= _other[i]->GetPhysicsComponent().GetPos().y + (_other[i]->GetPhysicsComponent().GetSize().y / 2))
				{
					//if dashing and collides with ground from top
					if (isDashing && physics->GetVelocity().y > 0)
					{
						locState = LocationState::ON_GROUND;
					}
					//if collides with ground normally 
					if (locState == LocationState::IN_AIR && physics->GetVelocity().y > 0)
					{
						//change state
						delete currentState;
						currentState = new StateStanding();
						currentState->Enter(*this);
					}
					//if climbing and on ground
					if (locState == LocationState::CLIMBING && physics->GetVelocity().y >= 0)
					{
						climbTimer = 0.0f;
					}
					inAir = false;
					break;
				}
				break;
			}
			case ObjectType::PLATFORM:
			{
				switch (std::get<0>(col))
				{
					case Direction::UP:
					{
						//if dashing and collides with ground from top
						if (isDashing && physics->GetVelocity().y > 0)
						{
							locState = LocationState::ON_GROUND;
						}
						//if collides with ground normally 
						if (locState == LocationState::IN_AIR && physics->GetVelocity().y > 0)
						{
							//change state
							delete currentState;
							currentState = new StateStanding();
							currentState->Enter(*this);
						}
						//if climbing and on ground
						if (locState == LocationState::CLIMBING && physics->GetVelocity().y >= 0)
						{
							climbTimer = 0.0f;
						}
						inAir = false;
						break;
					}

					case Direction::DOWN:
					{
						break;
					}

					case Direction::LEFT:
					{
						touchingSomethingLR = true;
						break;
					}

					case Direction::RIGHT:
					{
						touchingSomethingLR = true;
						break;
					}

					case Direction::NONE:
					{
						break;
					}

					default:
					{
						break;
					}
				}
				break;
			}
			case ObjectType::ACCELERATOR_PLATFORM:
			{
				switch (std::get<0>(col))
				{
					case Direction::UP:
					{
						//if dashing and collides with ground from top
						if (isDashing && physics->GetVelocity().y > 0)
						{
							locState = LocationState::ON_GROUND;
						}
						//if collides with ground normally 
						if (locState == LocationState::IN_AIR && physics->GetVelocity().y > 0)
						{
							//change state
							delete currentState;
							currentState = new StateStanding();
							currentState->Enter(*this);
						}
						//if climbing and on ground
						if (locState == LocationState::CLIMBING && physics->GetVelocity().y >= 0)
						{
							climbTimer = 0.0f;
						}

						if (locState == LocationState::ON_GROUND && !isDashing && _other[i]->GetPhysicsComponent().GetVelocity().y < 0)
						{
							if (Keyboard::KeyDown(GLFW_KEY_N))
							{
								PhysicsComponent otherPhys = _other[i]->GetPhysicsComponent();
								physics->Accelerate(otherPhys.GetVelocity() - glm::vec2(0.0f, JUMP_FORCE), 1.0f);
							}
						}
						inAir = false;
						break;
					}

					case Direction::DOWN:
					{
						PhysicsComponent otherPhys = _other[i]->GetPhysicsComponent();
						glm::vec2 distance = otherPhys.GetPos() - otherPhys.GetLastPos();
						pos += distance;
						break;
					}

					case Direction::LEFT:
					{
						touchingSomethingLR = true;
						if (locState == LocationState::CLIMBING)
						{
							PhysicsComponent otherPhys = _other[i]->GetPhysicsComponent();
							glm::vec2 distance = otherPhys.GetPos() - otherPhys.GetLastPos();
							pos += distance;
							/*if (!inputLocked)
							{
								if (Keyboard::KeyDown(GLFW_KEY_N) && otherPhys.GetVelocity().y < 0)
								{
									physics->Accelerate(otherPhys.GetVelocity() - glm::vec2(0.0f, JUMP_FORCE * .8f), 1.0f);
									StartInputLock(.25f);
								}
							}*/
						}
						break;
					}

					case Direction::RIGHT:
					{
						touchingSomethingLR = true;
						if (locState == LocationState::CLIMBING)
						{
							PhysicsComponent otherPhys = _other[i]->GetPhysicsComponent();
							glm::vec2 distance = otherPhys.GetPos() - otherPhys.GetLastPos();
							pos += distance;
							/*if (Keyboard::KeyDown(GLFW_KEY_N) && otherPhys.GetVelocity().y < 0)
							{
								physics->Accelerate(otherPhys.GetVelocity() - glm::vec2(0.0f, JUMP_FORCE * .8f), 1.0f);
								StartInputLock(1.0f);
							}*/
						}
						break;
					}

					case Direction::NONE:
					{
						break;
					}

					default:
					{
						break;
					}
				}
				break;
			}
			default:
			{
				break;
			}
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
	else if ((locState == LocationState::IN_AIR || locState == LocationState::CLIMBING) && touchingSomethingLR )
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
}

void Celeste::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
	physics->Render(_renderer);
}

LocationState& Celeste::GetLocationState()
{
	return locState;
}

bool Celeste::UseDash()
{
	if (dashCount > 0)
	{
		dashCount--;
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

bool Celeste::CanWallJump() const
{
	return wallJump;
}

bool Celeste::CanClimb() const
{
	return climb && climbTimer < MAX_CLIMB_DURATION;
}

bool Celeste::IsInputLocked() const
{
	return inputLocked;
}

//used for wall jumps
void Celeste::InputLockoutUpdate(GLfloat _dt)
{
	if (inputLocked)
	{
		lockoutTimer -= _dt;
		if (lockoutTimer <= 0)
		{
			inputLocked = false;
			lockoutTimer = 0.0f;
		}
	}
}

//used to prevent any input when walljumping. inputlocked will become false when celeste's y velocity is less than the min.
//so far, only stateinair checks for the lockout b/c of walljumping
void Celeste::StartInputLock(GLfloat _time)
{
	lockoutTimer = _time;
	inputLocked = true;
}

void Celeste::Respawn()
{
	pos = spawnLoc;
	physics->ResetVelY();
	physics->ResetVelX();
	direction = glm::ivec2(1, 0);
	facingDirection = 1;
	dashTimer = 0.0f;
	isDashing = false;
	dashCount = 1;
	wallJump = false;
	climb = false;
	climbTimer = 0.0f;
	isClimbing = false;

	delete currentState;
	currentState = new StateInAir();
	currentState->Enter(*this);
}
