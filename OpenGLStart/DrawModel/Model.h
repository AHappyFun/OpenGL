#pragma once
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include "stb_image.h"

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
public:
	Model(string path);

	~Model();

	void Draw(Shader* shader);
private:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;

	void LoadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

