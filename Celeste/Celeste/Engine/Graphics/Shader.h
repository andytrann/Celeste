#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader
{
public:
	Shader() { }

	// Sets the current shader as active
	Shader& Use();

	// Compiles the shader from given source code
	void    Compile(const GLchar* _vertexSource, const GLchar* _fragmentSource, const GLchar* _geometrySource = nullptr); // Note: geometry source code is optional 

	// Utility functions
	void    SetFloat(const GLchar* _name, GLfloat _value, GLboolean _useShader = false);
	void    SetInteger(const GLchar* _name, GLint _value, GLboolean _useShader = false);
	void    SetVector2f(const GLchar* _name, GLfloat _x, GLfloat _y, GLboolean _useShader = false);
	void    SetVector2f(const GLchar* _name, const glm::vec2& _value, GLboolean _useShader = false);
	void    SetVector3f(const GLchar* _name, GLfloat _x, GLfloat _y, GLfloat z, GLboolean _useShader = false);
	void    SetVector3f(const GLchar* _name, const glm::vec3& _value, GLboolean _useShader = false);
	void    SetVector4f(const GLchar* _name, GLfloat _x, GLfloat _y, GLfloat z, GLfloat w, GLboolean _useShader = false);
	void    SetVector4f(const GLchar* _name, const glm::vec4& _value, GLboolean _useShader = false);
	void    SetMatrix4(const GLchar* _name, const glm::mat4& _matrix, GLboolean _useShader = false);

	const GLuint& GetID() const;

private:
	// State
	GLuint ID;

	// Checks if compilation or linking failed and if so, print the error logs
	void    CheckCompileErrors(GLuint _object, std::string _type);
};

#endif
