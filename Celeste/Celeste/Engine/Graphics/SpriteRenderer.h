#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Texture2D;

class SpriteRenderer
{
public:
	SpriteRenderer(Shader& _shader);
	~SpriteRenderer();

	//Renders a defined quad textured with given sprite
	void DrawSprite(Texture2D& _texture, glm::vec2 _position, glm::vec2 _size = glm::vec2(10, 10),
		GLfloat _rotate = 0.0f, glm::vec3 _color = glm::vec3(1.0f));
private:
	//Initializes and configures the quad's buffer and vertex attributes
	void InitRenderData();

	//Render state
	Shader shader;
	GLuint quadVAO;
};

#endif
