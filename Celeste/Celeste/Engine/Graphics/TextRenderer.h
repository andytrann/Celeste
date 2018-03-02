#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <map>

//class Texture2D;

// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
	GLuint textureID;   // ID handle of the glyph texture
	glm::ivec2 size;    // Size of glyph
	glm::ivec2 bearing; // Offset from baseline to left/top of glyph
	GLuint advance;     // Horizontal offset to advance to next glyph
};

// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer
{
public:
	// Constructor
	TextRenderer(GLuint _width, GLuint _height);
	// Pre-compiles a list of characters from the given font
	void Load(std::string _font, GLuint _fontSize);
	// Renders a string of text using the precompiled list of characters
	void RenderText(std::string _text, GLfloat _x, GLfloat _y, GLfloat _scale, glm::vec3 _color = glm::vec3(1.0f));

private:
	// Holds a list of pre-compiled Characters
	std::map<GLchar, Character> characters;
	// Shader used for text rendering
	Shader textShader;

	// Render state
	GLuint VAO, VBO;
};

#endif
