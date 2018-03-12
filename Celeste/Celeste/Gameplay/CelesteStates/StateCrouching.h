#ifndef STATE_CROUCHING_H
#define STATE_CROUCHING_H

#include "CelesteState.h"

class StateCrouching : public CelesteState
{
public:
	CelesteState* HandleInput(Celeste& _celeste);
	//change sprite
	void Enter(Celeste& _celeste);
	LocationState GetState();
};

#endif