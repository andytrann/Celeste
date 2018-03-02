#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include "Texture2D.h"
#include "Shader.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

class SpriteRenderer;

/* EXPLAINS HOW THE CLASS WORKS MORE EASILY
Uses renderbuffer object to enable multisampling for anti-aliasing and attached to the multisampling framebuffer object.
Uses texture for postprocessing effects and is attached to the framebuffer object.
Binds multisampling frame buffer object to the READ_FRAMEBUFFER and the framebuffer object to the DRAW_FRAMEBUFFER.
Uses blit to copy pixels from READ_FRAMEBUFFER to DRAW_FRAMEBUFFER. Cant' use multisampling framebuffer for
postprocessing effects because theres too much data from the sampling. Framebuffer object now has normal texture
from the multisampling framebuffer information. Default framebuffer object is now bound.
Postprocessing effects are made, and default framebuffer draws the texture from the framebuffer object with the added effects.
*Note all of the object draw functions in Game::Render are being drawin to the multisampling frame buffer.
*/

// PostProcessor hosts all PostProcessing effects for the Breakout
// Game. It renders the game on a textured quad after which one can
// enable specific effects by enabling either the Confuse, Chaos or 
// Shake boolean. 
// It is required to call BeginRender() before rendering the game
// and EndRender() after rendering the game for the class to work.
class PostProcessor
{
public:
	// Constructor
	PostProcessor(Shader _shader, GLuint _width, GLuint _height);
	// Prepares the postprocessor's framebuffer operations before rendering the game
	void BeginRender();
	// Should be called after rendering the game, so it stores all the rendered data into a texture object
	void EndRender();
	// Renders the PostProcessor texture quad (as a screen-encompassing large sprite)
	void Render();

private:
	// Initialize quad for rendering postprocessing texture
	void InitRenderData();

	// State
	Shader postProcessingShader;
	Texture2D texture;
	GLuint width, height;

	// Render state
	GLuint MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
	GLuint RBO; // RBO is used for multisampled color buffer
	GLuint VAO;
};

#endif
