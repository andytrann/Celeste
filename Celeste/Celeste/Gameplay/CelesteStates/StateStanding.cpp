#include "StateStanding.h"

#include "../Celeste.h"
#include "../../Engine/IO/Keyboard.h"
#include "../../Engine/ResourceManager.h"

StateStanding::~StateStanding()
{
	//delete this;
}

CelesteState* StateStanding::HandleInput(Celeste& _celeste)
{
	if (Keyboard::KeyDown(GLFW_KEY_S))
	{
		//return new StateCrouching();
		return nullptr;
	}
	else
	{
		int direction = 0;
		if (Keyboard::Key(GLFW_KEY_D))
		{
			direction++;
		}
		if (Keyboard::Key(GLFW_KEY_A))
		{
			direction--;
		}

		_celeste.vel.x = (GLfloat)direction * _celeste.GetSpeed();

		return nullptr;
	}
}

void StateStanding::Update(Celeste& _celeste, GLfloat _dt)
{
	_celeste.pos += (_celeste.vel * _dt);
}

void StateStanding::Enter(Celeste& _celeste)
{

}