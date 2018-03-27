#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

class Celeste;

class PhysicsComponent
{
public:
	PhysicsComponent();
	void Update(Celeste& _celeste, float _dt);
private:
	void MaxFallSpeedDown();
	void MaxFallSpeedUp();

	float gravity;
	float maxFallSpeed;
	float climbUpSpeed;
	float climbDownSpeed;
};

#endif
