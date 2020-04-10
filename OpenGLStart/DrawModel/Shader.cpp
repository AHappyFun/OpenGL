#include "Shader.h"
#include <iostream>
#include <fstream>
#include<Sstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
Shader::Shader(const char* vertexPath,const char* fragmentPath, const char* geometryPath = nullptr)
{
	ifstream vertexFile;
	ifstream geomFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream geometrySStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(ifstream::failbit||ifstream::badbit);
	geomFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{
		if (!vertexFile.is_open()||!fragmentFile.is_open())
		{
			throw exception("open file error");
		}
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex,1,&vertexSource,NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex,"VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment,"FRAGMENT");
		
		unsigned int geometry;
		if (geometryPath != nullptr) {
			geomFile.open(geometryPath);
			geometrySStream << geomFile.rdbuf();
			geometryString = geometrySStream.str();
			geometrySource = geometryString.c_str();		
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &geometrySource, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}

		ID = glCreateProgram();
		glAttachShader(ID,vertex);
		glAttachShader(ID,fragment);
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);

		glLinkProgram(ID);
		checkCompileErrors(ID,"PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::SetUniform3f(const char * paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID,paramNameString),param.x,param.y,param.z);
}

void Shader::SetUniform1f(const char * paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString),param);
}

void Shader::SetUniform1i(const char * pargmNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID,pargmNameString),slot);
}

void Shader::checkCompileErrors(unsigned int ID, string type) {
	int success;
	char infoLog[512];

	if (type!="PROGRAM") {
		glGetShaderiv(ID,GL_COMPILE_STATUS,&success);
		if (!success)
		{
			glGetShaderInfoLog(ID,512,NULL,infoLog);
			cout << "shader comile error:" << infoLog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID,GL_LINK_STATUS,&success);
		if (!success)
		{
			glGetProgramInfoLog(ID,512,NULL,infoLog);
			cout << "program link error:" << infoLog << endl;
		}
	}
}

