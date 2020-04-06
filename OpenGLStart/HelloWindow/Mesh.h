#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"
#include <gl/glew.h>
using namespace std;

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texcoords;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	Mesh();
	Mesh(float vertices[]);
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

	~Mesh();

	//vector��c++�ṹ��һ������list�����ݽṹ
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	
	void Draw(Shader* shader);

private:
	//��Ⱦ����
	unsigned int VAO, VBO, EBO;

	void _setupMesh();
};

