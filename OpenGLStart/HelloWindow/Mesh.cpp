#include "Mesh.h"



Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

Mesh::Mesh(float vertices[])
{
	this->vertices.resize(36);
	memcpy(&(this->vertices[0]), vertices, 36 * 8 * sizeof(float));
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) 
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	_setupMesh();
}

void Mesh::_setupMesh() 
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Vertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));

	//Texcoord UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Texcoords));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader* shader) 
{
	//∞Û∂®Œ∆¿Ì
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1; 
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		//string number;
		string name = textures[i].type;
		
		if (name == "texture_diffuse") {
			glActiveTexture(GL_TEXTURE0);
			shader->SetUniform1i("material.diffuse", 0);
		}
		else if (name == "texture_specular") {
			glActiveTexture(GL_TEXTURE1);
			shader->SetUniform1i("material.specular", 1);
		}
		//else if (name == "texture_normal") {
		//	
		//}	
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//Draw Mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);

}