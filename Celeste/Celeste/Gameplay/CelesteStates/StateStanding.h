#ifndef STATE_STANDING_H
#define STATE_STANDING_H

#include "CelesteState.h"

class StateStanding : public CelesteState
{
public:
	CelesteState* HandleInput(Celeste& _celeste);
	void Update(Celeste& _celeste, GLfloat _dt);
	//change sprite
	void Enter(Celeste& _celeste);
	LocationState GetState();
};

#endif
