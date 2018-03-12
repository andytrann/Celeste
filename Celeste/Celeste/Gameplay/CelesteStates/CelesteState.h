#ifndef CELESTE_STATE_H
#define CELESTE_STATE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Celeste;
enum class LocationState
{
	ON_GROUND,
	IN_AIR,
	CLIMBING
};

class CelesteState
{
public:
	virtual ~CelesteState() {}
	virtual CelesteState* HandleInput(Celeste& _celeste) = 0;
	virtual void Enter(Celeste& _celeste) = 0;
	virtual LocationState GetState() = 0;
};

#endif
