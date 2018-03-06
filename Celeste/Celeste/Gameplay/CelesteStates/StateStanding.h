#ifndef STATE_STANDING_H
#define STATE_STANDING_H

#include "CelesteState.h"

class StateStanding : public CelesteState
{
public:
	~StateStanding();
	CelesteState* HandleInput(Celeste& _celeste);
	void Update(Celeste& _celeste, GLfloat _dt);

	//change sprite
	void Enter(Celeste& _celeste);
};

#endif
