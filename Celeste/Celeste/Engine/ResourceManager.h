#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <GL/glew.h>

#include <map>
#include <string>

class Texture2D;
class Shader;

// A static singleton ResourceManager class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined.

class ResourceManager
{
public:
	// Loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader LoadShader(const GLchar* _vShaderFile, const GLchar* _fShaderFile, const GLchar* _gShaderFile, std::string _name);
	// Retrieves a stored sader
	static Shader GetShader(std::string _name);

	// Loads (and generates) a texture from file
	static Texture2D LoadTexture(const GLchar* _file, GLboolean _alpha, std::string _name);
	// Retrieves a stored texture
	static Texture2D GetTexture(std::string _name);

	// Properly de-allocates all loaded resources
	static void Clear();

private:
	// Private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
	ResourceManager() { }
	// Loads and generates a shader from file
	static Shader LoadShaderFromFile(const GLchar* _vShaderFile, const GLchar* _fShaderFile, const GLchar* _gShaderFile = nullptr);
	// Loads a single texture from file
	static Texture2D LoadTextureFromFile(const GLchar* _file, GLboolean _alpha);

	// Resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;
};
#endif
