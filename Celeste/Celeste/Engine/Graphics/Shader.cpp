#include "Shader.h"

#include <iostream>

Shader &Shader::Use()
{
	glUseProgram(ID);
	return *this;
}

void Shader::Compile(const GLchar* _vertexSource, const GLchar* _fragmentSource, const GLchar* _geometrySource)
{
	GLuint sVertex, sFragment, gShader;
	// Vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &_vertexSource, NULL);
	glCompileShader(sVertex);
	CheckCompileErrors(sVertex, "VERTEX");

	// Fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &_fragmentSource, NULL);
	glCompileShader(sFragment);
	CheckCompileErrors(sFragment, "FRAGMENT");

	// If geometry shader source code is given, also compile geometry shader
	if (_geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &_geometrySource, NULL);
		glCompileShader(gShader);
		CheckCompileErrors(gShader, "GEOMETRY");
	}

	// Shader Program
	ID = glCreateProgram();
	glAttachShader(ID, sVertex);
	glAttachShader(ID, sFragment);
	if (_geometrySource != nullptr)
		glAttachShader(ID, gShader);
	glLinkProgram(ID);
	CheckCompileErrors(ID, "PROGRAM");

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (_geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::SetFloat(const GLchar* _name, GLfloat _value, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform1f(glGetUniformLocation(ID, _name), _value);
}

void Shader::SetInteger(const GLchar* _name, GLint _value, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform1i(glGetUniformLocation(ID, _name), _value);
}

void Shader::SetVector2f(const GLchar* _name, GLfloat _x, GLfloat _y, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform2f(glGetUniformLocation(ID, _name), _x, _y);
}

void Shader::SetVector2f(const GLchar* _name, const glm::vec2& _value, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform2f(glGetUniformLocation(ID, _name), _value.x, _value.y);
}

void Shader::SetVector3f(const GLchar* _name, GLfloat _x, GLfloat _y, GLfloat _z, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform3f(glGetUniformLocation(ID, _name), _x, _y, _z);
}

void Shader::SetVector3f(const GLchar* _name, const glm::vec3& _value, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform3f(glGetUniformLocation(ID, _name), _value.x, _value.y, _value.z);
}

void Shader::SetVector4f(const GLchar* _name, GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform4f(glGetUniformLocation(ID, _name), _x, _y, _z, _w);
}

void Shader::SetVector4f(const GLchar* _name, const glm::vec4& _value, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniform4f(glGetUniformLocation(ID, _name), _value.x, _value.y, _value.z, _value.w);
}

void Shader::SetMatrix4(const GLchar* _name, const glm::mat4& _matrix, GLboolean _useShader)
{
	if (_useShader)
		Use();
	glUniformMatrix4fv(glGetUniformLocation(ID, _name), 1, GL_FALSE, glm::value_ptr(_matrix));
}

const GLuint & Shader::GetID() const
{
	return ID;
}

void Shader::CheckCompileErrors(GLuint _object, std::string _type)
{
	GLint success;
	GLchar infoLog[1024];
	if (_type != "PROGRAM")
	{
		glGetShaderiv(_object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << _type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(_object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(_object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << _type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}