#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);
	string vertexString;
	string geometryString;
	string fragmentString;
	const char* vertexSource;
	const char* geometrySource;
	const char* fragmentSource;
	unsigned int ID;   //shader program ID
	void use();
	void SetUniform3f(const char* paramNameString,glm::vec3 param);
	void SetUniform1f(const char* paramNameString,float param);
	void SetUniform1i(const char* pargmNameString,int slot);
private:
	void checkCompileErrors(unsigned int ID,string type);
};

