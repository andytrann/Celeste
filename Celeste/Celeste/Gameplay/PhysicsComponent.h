#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

class Celeste;

class PhysicsComponent
{
public:
	void Update(Celeste& _celeste, float _dt);
private:
	void MaxFallSpeedDown();
	void MaxFallSpeedUp();

	static float GRAVITY;
	static float MAX_FALL_SPEED;
};

#endif
