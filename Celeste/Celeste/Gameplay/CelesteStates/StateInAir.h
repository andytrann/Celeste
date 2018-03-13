#ifndef STATE_IN_AIR_H
#define STATE_IN_AIR_H

#include "CelesteState.h"

class StateInAir : public CelesteState
{
public:
	CelesteState* HandleInput(Celeste& _celeste, GLfloat _dt);
	//change sprite
	void Enter(Celeste& _celeste);
	LocationState GetState();
};

#endif
