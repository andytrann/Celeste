#include "ResourceManager.h"

#include "Graphics/Texture2D.h"
#include "Graphics/Shader.h"

#include <SOIL\src\SOIL.h>

#include <iostream>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::LoadShader(const GLchar* _vShaderFile, const GLchar* _fShaderFile, const GLchar* _gShaderFile, std::string _name)
{
	shaders[_name] = LoadShaderFromFile(_vShaderFile, _fShaderFile, _gShaderFile);
	return shaders[_name];
}

Shader ResourceManager::GetShader(std::string _name)
{
	return shaders[_name];
}

Texture2D ResourceManager::LoadTexture(const GLchar* _file, GLboolean _alpha, std::string _name)
{
	textures[_name] = LoadTextureFromFile(_file, _alpha);
	return textures[_name];
}

Texture2D ResourceManager::GetTexture(std::string _name)
{
	return textures[_name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : shaders)
		glDeleteProgram(iter.second.GetID());
	// (Properly) delete all textures
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.GetID());
}

Shader ResourceManager::LoadShaderFromFile(const GLchar* _vShaderFile, const GLchar* _fShaderFile, const GLchar* _gShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(_vShaderFile);
		std::ifstream fragmentShaderFile(_fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (_gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(_gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, _gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::LoadTextureFromFile(const GLchar* _file, GLboolean _alpha)
{
	// Create Texture object
	Texture2D texture;
	if (_alpha)
	{
		texture.SetInternalFormat(GL_RGBA);
		texture.SetImageFormat(GL_RGBA);
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(_file, &width, &height, 0, texture.GetImageFormat() == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}