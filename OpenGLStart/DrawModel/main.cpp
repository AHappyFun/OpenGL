#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Material.h"
#include "LightDirection.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma region Model Data ģ������
GLfloat skyboxVertices[] = {
	// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
};
#pragma endregion

#pragma region Init Camera ��ʼ�������
//Instantiate Camera Class
// camera(glm::vec3(0,0,3.0f),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));   ��һ��
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));   //�ڶ���
#pragma endregion

#pragma region Init Light ��ʼ���ƹ�
//LightSpot light (glm::vec3(0,5.0f,0),glm::vec3(90.0f,0,0),glm::vec3(1.0f, 1.0f, 0.0f));

LightDirection light(glm::vec3(0, 5.0f, 0), glm::vec3(90.0f, 0, 0), glm::vec3(0.2f, 0.2f, 0.2f));

#pragma endregion

#pragma region Input  �������
float lastX;
float lastY;
bool firstMouse = true;

void processInput(GLFWwindow* window) {    //������esc���رմ���
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.SpeedZ = 1.0f;
		camera.MoveZ();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.SpeedZ = -1.0f;
		camera.MoveZ();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.SpeedX = -1.0f;
		camera.MoveX();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.SpeedX = 1.0f;
		camera.MoveX();
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.SpeedY = 1.0f;
		camera.MoveY();
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.SpeedY = -1.0f;
		camera.MoveY();
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;
	cout << deltaX << endl;
	camera.ProcessMouseMovement(deltaX, deltaY);
}

#pragma endregion

unsigned int LoadImageToGpu(const char* fileName, GLint internal, GLenum format, int texPlus) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + texPlus);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Load Image Failed.";
	}
	stbi_image_free(data);
	return TexBuffer;
}

unsigned int loadCubemap(vector<string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

int main(int argc, char* argv[]) {

	std::string exePath = argv[0];

	# pragma region OpenWindow  ����һ������
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Open GLFW Window --GLFW��һ����ƽ̨��OpenGLӦ�ÿ�ܣ�֧�ִ��ڴ���������������¼��ȹ��ܡ�
		GLFWwindow* window = glfwCreateWindow(800, 600, "First OpenGL", NULL, NULL);
		if (window == NULL) {
			printf("Open Window Failed.");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //�ر����ָ��
		glfwSetCursorPosCallback(window, mouse_callback);

		//Init GLEW  --GLEW��һ������OpenGLͼ�νӿڵĿ�ƽ̨��C++��չ�⡣GLEW���Զ�ʶ��ǰƽ̨��֧�ֵ�ȫ��OpenGL�߼���չ������ֻҪ����glew.hͷ�ļ�������ʹ��gl,glu,glext,wgl,glx��ȫ��������
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			printf("Init GLEW failed.");
			glfwTerminate();
			return -1;
		}
		glViewport(0, 0, 800, 600);
	#pragma endregion

	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	Shader* lineShader = new Shader("vertexSource.vert", "outline.frag");
	Shader* skyboxShader = new Shader("skyboxVert.vert", "skyboxFrag.frag");
	

	//Material *myMaterial = new Material(myShader,
	//									LoadImageToGpu("container2.png",GL_RGBA,GL_RGBA,0),
	//									LoadImageToGpu("container2_specular.png", GL_RGBA, GL_RGBA, 1),
	//									glm::vec3(1.0f, 1.0f, 1.0f),
	//									LoadImageToGpu("emission.jpg", GL_RGB, GL_RGB, 2),
	//									32.0f);

	# pragma region ����ģ�� ��VAO��VBO		
		
		//skybox VAO
		unsigned int skyboxVAO, skyboxVBO;
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);

		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\nanosuit\\nanosuit.obj");
		
	#pragma endregion

	#pragma region  Load Texture 
		vector<string> faces
		{
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			"front.jpg",
			"back.jpg"
		};
		unsigned int cubemapTexture = loadCubemap(faces);
#pragma endregion

		skyboxShader->use();
		glUniform1i(glGetUniformLocation(skyboxShader->ID, "skybox"), 0);

	#pragma region MVP matrix Init ����MVP����
		glm::mat4 viewMat;
		//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));	
		glm::mat4 projectionMat;
		projectionMat = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	#pragma endregion

	#pragma region  Draw State Set  ����GL����״̬(����)
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //�߿�ģʽ
			glEnable(GL_DEPTH_TEST);   //������Ȳ���

			glEnable(GL_CULL_FACE); //�������޳���Ĭ���޳�����
			//glCullFace(GL_FRONT);

			glEnable(GL_STENCIL_TEST);  //����ģ�����
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); 


	#pragma endregion

	while (!glfwWindowShouldClose(window))
	{
		// ��������
		processInput(window);

		//render command
		//Clear
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);  //��ӦUnity�е������clearģʽ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);   

		//��պл���
		glDepthMask(GL_FALSE);
		skyboxShader->use();
		viewMat = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader->ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
		
		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);

		//---��������---
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);

		myShader->use();

		viewMat = camera.GetViewMatrix();   //��Ҫ��whileѭ����仯
		
		for (int i = 0; i < 1; i++)
		{
			// Matrix �任
			glm::mat4 modelMat;
			modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f));
			modelMat = glm::rotate(modelMat, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			modelMat = glm::scale(modelMat, glm::vec3(0.2f, 0.2f, 0.2f));

			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
			glUniform3f(glGetUniformLocation(myShader->ID,"ambientColor"),0.5f,0.5f,0.5f);
			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			
			glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), light.position.x, light.position.y, light.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), light.color.x, light.color.y, light.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightDirectionUniform"), light.direction.x, light.direction.y, light.direction.z);
		
		
			//����Cam worldPos
			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			model.Draw(myShader);
		}	

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		lineShader->use();

		for (int i = 0; i < 1; i++)
		{
			// Matrix �任
			glm::mat4 modelMat;
			modelMat = glm::translate(modelMat, glm::vec3(0.0f, -0.05f, 0.0f));
			modelMat = glm::rotate(modelMat, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			modelMat = glm::scale(modelMat, glm::vec3(0.205f, 0.205f, 0.205f));

			glUniformMatrix4fv(glGetUniformLocation(lineShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(lineShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(lineShader->ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
			glUniform3f(glGetUniformLocation(lineShader->ID, "ambientColor"), 0.5f, 0.5f, 0.5f);
			glUniform3f(glGetUniformLocation(lineShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);

			glUniform3f(glGetUniformLocation(lineShader->ID, "lightPos"), light.position.x, light.position.y, light.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), light.color.x, light.color.y, light.color.z);
			//glUniform3f(glGetUniformLocation(myShader->ID, "lightDirectionUniform"), light.direction.x, light.direction.y, light.direction.z);


			//����Cam worldPos
			glUniform3f(glGetUniformLocation(lineShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			model.Draw(lineShader);
		}

		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);


		//check and call events and swap the buffers
		glfwSwapBuffers(window); //����˫����
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
