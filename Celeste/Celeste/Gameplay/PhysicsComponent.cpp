#include "PhysicsComponent.h"

#include "Celeste.h"
#include "../Engine/ResourceManager.h"

PhysicsComponent::PhysicsComponent(GameObject & _object, glm::vec2 _TLOffset, glm::vec2 _size, GLfloat _gravity, GLfloat _maxSpeed, GLfloat _gFric, GLfloat _aFric) : 
	gameObject(_object),
	TLOffset(_TLOffset),
	vel(glm::vec2(0.0f, 0.0f)),
	size(_size),
	gravity(_gravity),
	maxSpeed(_maxSpeed),
	groundFriction(_gFric),
	airFriction(_aFric),
	lastPos(gameObject.pos + TLOffset)
{
	sprite = ResourceManager::GetTexture("Exit");
}

void PhysicsComponent::Update(GLboolean _affByGrav, GLfloat _dt)
{
	lastPos = GetPos();
	if (vel.y < maxSpeed && _affByGrav)
	{
		Accelerate(glm::vec2(0.0f, gravity), _dt);
	}
	gameObject.pos += (vel * _dt);
}

void PhysicsComponent::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, gameObject.pos + TLOffset, size, gameObject.rot);
}

void PhysicsComponent::Accelerate(glm::vec2 _amt, GLfloat _dt)
{
	vel += (_amt * _dt);
}

glm::vec2 PhysicsComponent::GetPos() const
{
	return gameObject.pos + TLOffset;
}

glm::vec2 PhysicsComponent::GetSize() const
{
	return size;
}

glm::vec2 PhysicsComponent::GetVelocity() const
{
	return vel;
}

void PhysicsComponent::SetVelX(GLfloat _amt)
{
	vel.x = _amt;
}

void PhysicsComponent::SetVelY(GLfloat _amt)
{
	vel.y = _amt;
}

void PhysicsComponent::ResetVelY()
{
	vel.y = 0.0f;
}

void PhysicsComponent::ResetVelX()
{
	vel.x = 0.0f;
}

void PhysicsComponent::ApplyGroundFriction(glm::vec2 _dir)
{
	vel *= (_dir * groundFriction);
}

void PhysicsComponent::ApplyAirFriction()
{
	vel.x *= airFriction;
}

//helper function for GetCollision
GLboolean PhysicsComponent::CheckCollision(PhysicsComponent& _other)
{
	/*glm::vec2 rbPos = GetPos();
	glm::vec2 otherRbPos = _other.GetPos();
	//collisions arent supposed to use =, but will fix later
	// Collision x - axis ?
	bool collisionX = rbPos.x + size.x >= otherRbPos.x &&
		otherRbPos.x + _other.GetSize().x >= rbPos.x;
	// Collision y-axis?
	bool collisionY = rbPos.y + size.y >= otherRbPos.y &&
		otherRbPos.y + _other.GetSize().y >= rbPos.y;

	// Collision only if on both axes
	return collisionX && collisionY;*/

	GLfloat w = .5f * (size.x + _other.size.x);
	GLfloat h = .5f * (size.y + _other.size.y);
	GLfloat dx = (GetPos().x + (size.x / 2.0f)) - (_other.GetPos().x + (_other.GetSize().x / 2.0f));
	GLfloat dy = (GetPos().y + (size.y / 2.0f)) - (_other.GetPos().y + (_other.GetSize().y / 2.0f));
	return abs(dx) <= w && abs(dy) <= h;
}

//slight bug with colliding with platfrom from top right and bottom left corner from above/below.
Collision PhysicsComponent::GetCollision(PhysicsComponent& _other) // AABB collision
{
	if (CheckCollision(_other))
	{
		glm::vec2 rbPos = GetPos();
		glm::vec2 otherRbPos = _other.GetPos();

		// Get center point of celeste first 
		glm::vec2 center(rbPos.x + (size.x / 2.0f), rbPos.y + (size.y / 2.0f));
		// Calculate AABB info (center, half-extents)
		glm::vec2 aabb_half_extents(_other.GetSize().x / 2.0f, _other.GetSize().y / 2.0f);
		glm::vec2 aabb_center(
			otherRbPos.x + aabb_half_extents.x,
			otherRbPos.y + aabb_half_extents.y
		);
		// Get difference vector between both centers
		glm::vec2 difference = center - aabb_center;

		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		// Add clamped value to AABB_center and we get the value of box closest to celeste
		glm::vec2 closest = aabb_center + clamped;
		// Retrieve vector between center of celeste and closest point AABB
		difference = closest - center;

		//grab direction of collision relative to _other
		/*glm::vec2 sizeNormalized(glm::normalize(size));
		glm::vec2 compass[] = {
			glm::vec2(0.0f, sizeNormalized.x),	// up
			glm::vec2(-sizeNormalized.y, 0.0f),	// left
			glm::vec2(0.0f, -sizeNormalized.x),	// down
			glm::vec2(sizeNormalized.y, 0.0f)	// right
		};
		GLfloat max = 0.0f;
		GLuint best_match = -1;
		for (GLuint i = 0; i < 4; i++)
		{
			GLfloat dot_product = glm::dot(glm::normalize(difference), compass[i]);
			if (dot_product > max)
			{
				max = dot_product;
				best_match = i;
			}
		}
		return std::make_tuple((Direction)best_match, difference);*/

		GLfloat w = .5f * (size.x + _other.size.x);
		GLfloat h = .5f * (size.y + _other.size.y);
		GLfloat dx = GetPos().x + (size.x / 2.0f) - aabb_center.x;
		GLfloat dy = GetPos().y + (size.y / 2.0f) - aabb_center.y;
		//GLfloat dx = lastPos.x + (size.x / 2.0f) - aabb_center.x;
		//GLfloat dy = lastPos.y + (size.y / 2.0f) - aabb_center.y;


		GLfloat wy = w * dy;
		GLfloat hx = h * dx;
		if (wy > hx)
		{
			if (wy > -hx)
			{
				return std::make_tuple(Direction::DOWN, difference);
			}
			else
			{
				return std::make_tuple(Direction::LEFT, difference);
			}
		}
		else
		{
			if (wy > -hx)
			{
				return std::make_tuple(Direction::RIGHT, difference);
			}
			else
			{
				return std::make_tuple(Direction::UP, difference);
			}
		}
	}
	else
	{
		return std::make_tuple(Direction::NONE, glm::vec2(0));
	}
}
