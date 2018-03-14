#ifndef STATE_DASHING_H
#define STATE_DASHING_H

#include "CelesteState.h"

class StateDashing : public CelesteState
{
public:
	CelesteState* HandleInput(Celeste& _celeste, GLfloat _dt);
	//change sprite
	void Enter(Celeste& _celeste);
};

#endif