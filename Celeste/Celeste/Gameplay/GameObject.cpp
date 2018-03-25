#include "GameObject.h"

GameObject::GameObject() : 
	pos(0, 0),
	size(1, 1),
	vel(0.0f),
	color(1.0f),
	rot(0.0f),
	sprite(),
	destroyed(false),
	objectType(ObjectType::NONE)
{
}

GameObject::GameObject(glm::vec2 _pos, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color, glm::vec2 _vel) : 
	pos(_pos),
	size(_size),
	vel(_vel),
	color(_color),
	rot(0.0f),
	sprite(_sprite),
	destroyed(false),
	objectType(ObjectType::NONE)
{
}

void GameObject::Render(SpriteRenderer & _renderer)
{
	_renderer.DrawSprite(sprite, pos, size, rot, color);
}

ObjectType GameObject::GetType() const
{
	return objectType;
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
			glm::vec2 compass[] = {
				glm::vec2(0.0f, .5f),	// up
				glm::vec2(-1.0f, 0.0f),	// left
				glm::vec2(0.0f, -.5f),	// down
				glm::vec2(1.f, 0.0f)	// right
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