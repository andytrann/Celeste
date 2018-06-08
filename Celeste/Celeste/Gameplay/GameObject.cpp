#include "GameObject.h"

#include "PhysicsComponent.h"

GameObject::GameObject() : 
	pos(0, 0),
	size(1, 1),
	color(1.0f),
	rot(0.0f),
	sprite(),
	destroyed(false),
	objectType(ObjectType::NONE)
{
	physics = nullptr;
}

GameObject::GameObject(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color, glm::vec2 _vel) : 
	pos(_pos),
	size(_size),
	color(_color),
	rot(0.0f),
	sprite(_sprite),
	destroyed(false),
	objectType(ObjectType::NONE)
{
	physics = nullptr;
}

GameObject::~GameObject()
{
	delete physics;
	physics = nullptr;
}

void GameObject::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

ObjectType GameObject::GetType() const
{
	return objectType;
}

void GameObject::CreatePhysicsComponent(glm::vec2 _TLOffset, glm::vec2 _size, GLfloat _gravity, GLfloat _maxSpeed, GLfloat _gFric, GLfloat _aFric)
{
	if (physics == nullptr)
	{
		physics = new PhysicsComponent(*this, _TLOffset, _size, _gravity, _maxSpeed, _gFric, _aFric);
	}
}

PhysicsComponent & GameObject::GetPhysicsComponent()
{
	return *physics;
}

//helper function for GetCollision
GLboolean GameObject::CheckCollision(GameObject& _other)
{
	// Collision x - axis ?
	bool collisionX = pos.x + size.x >= _other.pos.x &&
		_other.pos.x + _other.size.x >= pos.x;
	// Collision y-axis?
	bool collisionY = pos.y + size.y >= _other.pos.y &&
		_other.pos.y + _other.size.y >= pos.y;

	// Collision only if on both axes
	return collisionX && collisionY;
}

Collision GameObject::GetCollision(GameObject& _other) // AABB collision
{
	//need to fix how direction is calculated. will need to keep track of previous position to get correct direction.
	if (CheckCollision(_other))
	{
		// Get center point of celeste first 
		glm::vec2 center(pos.x + (size.x / 2.0f), pos.y + (size.y / 2.0f));
		// Calculate AABB info (center, half-extents)
		glm::vec2 aabb_half_extents(_other.size.x / 2.0f, _other.size.y / 2.0f);
		glm::vec2 aabb_center(
			_other.pos.x + aabb_half_extents.x,
			_other.pos.y + aabb_half_extents.y
		);
		// Get difference vector between both centers
		glm::vec2 difference = center - aabb_center;

		glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
		// Add clamped value to AABB_center and we get the value of box closest to celeste
		glm::vec2 closest = aabb_center + clamped;
		// Retrieve vector between center of celeste and closest point AABB
		difference = closest - center;

		//grab direction of collision relative to _other
		//if (difference.x <= size.x / 2.0f && difference.y <= size.y / 2.0f)
		//{
		glm::vec2 sizeNormalized(glm::normalize(size));
		glm::vec2 compass[] = {
			glm::vec2(0.0f, sizeNormalized.y),	// up
			glm::vec2(-sizeNormalized.x, 0.0f),	// left
			glm::vec2(0.0f, -sizeNormalized.y),	// down
			glm::vec2(sizeNormalized.x, 0.0f)	// right
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
		return std::make_tuple((Direction)best_match, difference);
		//}
	}
	else
	{
		return std::make_tuple(Direction::NONE, glm::vec2(0));
	}
}