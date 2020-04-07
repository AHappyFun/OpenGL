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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma region Model Data 模型数据

GLfloat vertices[] = {
	// Positions          // Normals           // Texture Coords UV
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region Init Camera 初始化摄像机
//Instantiate Camera Class
// camera(glm::vec3(0,0,3.0f),glm::vec3(0,0,0),glm::vec3(0,1.0f,0));   第一种
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));   //第二种
#pragma endregion

#pragma region Init Light 初始化灯光
//LightSpot light (glm::vec3(0,5.0f,0),glm::vec3(90.0f,0,0),glm::vec3(1.0f, 1.0f, 1.0f));

LightDirection light(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 0.0f));

#pragma endregion

#pragma region Input  检测输入
float lastX;
float lastY;
bool firstMouse = true;

void processInput(GLFWwindow* window) {    //如果点击esc，关闭窗口
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

int main() {
	# pragma region OpenWindow  创建一个窗口
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Open GLFW Window --GLFW是一个跨平台的OpenGL应用框架，支持窗口创建，接受输入和事件等功能。
		GLFWwindow* window = glfwCreateWindow(800, 600, "First OpenGL", NULL, NULL);
		if (window == NULL) {
			printf("Open Window Failed.");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //关闭鼠标指针
		glfwSetCursorPosCallback(window, mouse_callback);

		//Init GLEW  --GLEW是一个基于OpenGL图形接口的跨平台的C++扩展库。GLEW能自动识别当前平台所支持的全部OpenGL高级扩展涵数。只要包含glew.h头文件，就能使用gl,glu,glext,wgl,glx的全部函数。
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			printf("Init GLEW failed.");
			glfwTerminate();
			return -1;
		}
		glViewport(0, 0, 800, 600);
	#pragma endregion

	Shader* myShader = new  Shader("vertexSource.vert", "fragmentSource.frag");

	Material *myMaterial = new Material(myShader,
										LoadImageToGpu("container2.png",GL_RGBA,GL_RGBA,0),
										LoadImageToGpu("container2_specular.png", GL_RGBA, GL_RGBA, 1),
										glm::vec3(1.0f, 1.0f, 1.0f),
										LoadImageToGpu("emission.jpg", GL_RGB, GL_RGB, 2),
										32.0f);

	# pragma region 加载模型 绑定VAO和VBO		
		
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		/*unsigned int EBO;     //EBO索引模式
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

		// 位置属性
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// 颜色属性
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);

		//Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//UV
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	#pragma endregion

	#pragma region Init and Load Texture
		/*unsigned int TexBufferA;
		TexBufferA = LoadImageToGpu("container.jpg", GL_RGB, GL_RGB, 0);
		unsigned int TexBufferB;
		TexBufferB = LoadImageToGpu("awesomeface.png", GL_RGBA, GL_RGBA, 0);*/
	#pragma endregion

	#pragma region MVP matrix Init 创建MVP矩阵
		glm::mat4 viewMat;
		//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));	
		glm::mat4 projectionMat;
		projectionMat = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	#pragma endregion

	#pragma region  Draw State Set  设置GL绘制状态(命令)
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //线框模式
			
			//glEnable(GL_STENCIL_TEST); // 开启模板测试


			glEnable(GL_DEPTH_TEST);   //开启深度测试
			glDepthFunc(GL_LESS);
	#pragma endregion

	while (!glfwWindowShouldClose(window))
	{
		// 接收输入
		processInput(window);

		//render command
		//Clear
		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //对应Unity中的摄像机clear模式

		viewMat = camera.GetViewMatrix();   //需要在while循环里变化

		for (int i = 0; i < 10; i++)
		{
			//MVP Matrix 变换
			glm::mat4 modelMat;
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			
			//Set Material --> 1Shader Program
			myShader->use();

			//Set Material --> 2Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
			glActiveTexture(GL_TEXTURE0 + 2);
			glBindTexture(GL_TEXTURE_2D, myMaterial->emission);

			//Set Material --> 3Uniforms
			glUniform1i(glGetUniformLocation(myShader->ID, "myTexture"), 0);
			glUniform1i(glGetUniformLocation(myShader->ID, "myFaceTex"), 1);
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projectionMat"), 1, GL_FALSE, glm::value_ptr(projectionMat));
			glUniform3f(glGetUniformLocation(myShader->ID,"ambientColor"),0.5f,0.5f,0.5f);
			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			
			glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), light.position.x, light.position.y, light.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), light.color.x, light.color.y, light.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightDirectionUniform"), light.direction.x, light.direction.y, light.direction.z);

			// Spot 聚光灯的Phy角的大小
			/*
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), light.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOutter"), light.cosPhyOutter);
			*/

			//点光源的衰减 attenuation
			/*
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.constant"), light.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.linear"), light.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP.quadratic"), light.quadratic);
			*/

			//设置Cam worldPos
			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			myMaterial->shader->SetUniform3f("material.ambient",myMaterial->ambient);
			//myMaterial->shader->SetUniform1i("material.diffuse", myMaterial->diffuse);
			myMaterial->shader->SetUniform1i("material.diffuse",0);
			myMaterial->shader->SetUniform1i("material.specular",1);
			myMaterial->shader->SetUniform1i("material.emission",2);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);

			//Set Model
			glBindVertexArray(VAO);

			//Draw Call
			//glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);
			glDrawArrays(GL_TRIANGLES, 0, 36);    //Draw Call 10次
		}

		//check and call events and swap the buffers
		glfwSwapBuffers(window); //交换双缓冲
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
