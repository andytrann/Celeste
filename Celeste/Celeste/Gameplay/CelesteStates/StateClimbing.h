#ifndef STATE_CLIMBING_H
#define STATE_CLIMBING_H

#include "CelesteState.h"

class StateClimbing : public CelesteState
{
public:
	CelesteState * HandleInput(Celeste& _celeste, GLfloat _dt);
	//change sprite
	void Enter(Celeste& _celeste);
};

#endif