#pragma once
#include "Mesh.h"
#include <vector>

class Model
{
public:
	Model(char *path);

	~Model();

	void Draw(Shader* shader);
private:
	vector<Mesh> meshes;
	string directory;

	void LoadModel(string path);
	//void processNode(aiNode *node)
};

