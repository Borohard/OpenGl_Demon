#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Object.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void Do_Movement();

void ListenEvents();

void SetView(int width, int height, Shader& ourShader);

void getVertex(std::vector<float>& verticesData, int figure);

void getIndex(std::vector<int>& indexData, int chouse);


Camera camera(glm::vec3(0.0f, 0.5f, 5.0f));
bool keys[1024];
GLfloat lastX = 800, lastY = 450;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1600, 900, "Cacodemon", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader ourShader("Shaders/shader.vs", "Shaders/shader.frag");

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// ОБЪЕКТЫ СЦЕНЫ
	std::vector<float> floorVertData;
	std::vector<int> floorIndexData;
	getVertex(floorVertData, 1);
	getIndex(floorIndexData, 1);
	Object floor;
	floor.SetVerticlesAndIndeсes(floorVertData, floorIndexData);
	floor.SetTexture("Textures/hell.png");

	std::vector<float> teethVertData;
	std::vector<int> teethIndData;
	getVertex(teethVertData, 2);
	getIndex(teethIndData, 2);
	Object teeth;
	teeth.SetVerticlesAndIndeсes(teethVertData, teethIndData);
	teeth.SetTexture("Textures/teeth.png");

	std::vector<float> hornVertData;
	std::vector<int> hornIndData;
	getVertex(hornVertData, 3);
	getIndex(hornIndData, 3);
	Object horn;
	horn.SetVerticlesAndIndeсes(hornVertData, hornIndData);
	horn.SetTexture("Textures/horn.png");

	std::vector<float> bodyVertData;
	std::vector<int> bodyIndData;
	getVertex(bodyVertData, 4);
	getIndex(bodyIndData, 4);
	Object body;
	body.SetVerticlesAndIndeсes(bodyVertData, bodyIndData);
	body.SetTexture("Textures/body.png");

	std::vector<float> eyeVertData;
	std::vector<int> eyeIndData;
	getVertex(eyeVertData, 5);
	getIndex(eyeIndData, 5);
	Object eye;
	eye.SetVerticlesAndIndeсes(eyeVertData, eyeIndData);
	eye.SetTexture("Textures/eye.png");

	std::vector<float> mouthVertData;
	std::vector<int> mouthIndData;
	getVertex(mouthVertData, 6);
	getIndex(mouthIndData, 6);
	Object mouth;
	mouth.SetVerticlesAndIndeсes(mouthVertData, mouthIndData);
	mouth.SetTexture("Textures/mouth.png");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		ListenEvents();
		glClearColor(0.41f, 0.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();
		SetView(width, height, ourShader);

		floor.SetTranslate(glm::vec3(0, -1, 0));
		floor.SetScale(glm::vec3(200, 200, 200));
		floor.Draw(ourShader);

		teeth.SetTranslate(glm::vec3(0, 0.0, 0.6));
		teeth.SetScale(glm::vec3(0.8, 0.8, 0.8));
		teeth.SetRotate(15.0f, glm::vec3(-1.0, 0.0, 0.0));
		teeth.Draw(ourShader);

		teeth.SetTranslate(glm::vec3(0, -0.1, 0.65));
		teeth.SetScale(glm::vec3(0.8, 0.8, 0.8));
		teeth.SetRotate(180.0f, glm::vec3(0.0, 0.0, 1.0));
		teeth.SetRotate(35.0f, glm::vec3(-1.0, 0.0, 0.0));
		teeth.Draw(ourShader);

		//первые шесть
		horn.SetTranslate(glm::vec3(-0.4, 1.0, 0.45));
		horn.SetScale(glm::vec3(0.5, 0.5, 0.5));
		horn.SetRotate(15.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(0.4, 1.0, 0.45));
		horn.SetScale(glm::vec3(0.5, 0.5, 0.5));
		horn.SetRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		horn.SetRotate(-15.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(-0.55, 1.0, 0.0));
		horn.SetScale(glm::vec3(0.4, 0.4, 0.4));
		horn.SetRotate(20.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(0.55, 1.0, 0.0));
		horn.SetScale(glm::vec3(0.4, 0.4, 0.4));
		horn.SetRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		horn.SetRotate(20.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(-0.5, 0.9, -0.4));
		horn.SetScale(glm::vec3(0.3, 0.3, 0.3));
		horn.SetRotate(-20.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(0.5, 0.9, -0.4));
		horn.SetScale(glm::vec3(0.3, 0.3, 0.3));
		horn.SetRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		horn.SetRotate(20.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.Draw(ourShader);

		//вторые
		horn.SetTranslate(glm::vec3(-0.7, 0.55, 0.5));
		horn.SetScale(glm::vec3(0.3, 0.3, 0.3));
		horn.SetRotate(45.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.SetRotate(45.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(0.7, 0.55, 0.5));
		horn.SetScale(glm::vec3(0.3, 0.3, 0.3));
		horn.SetRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		horn.SetRotate(-45.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.SetRotate(45.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(-0.8, 0.65, 0.05));
		horn.SetScale(glm::vec3(0.3, 0.3, 0.3));
		horn.SetRotate(20.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.SetRotate(45.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(0.8, 0.65, 0.05));
		horn.SetScale(glm::vec3(0.3, 0.3, 0.3));
		horn.SetRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		horn.SetRotate(-20.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.SetRotate(45.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(-0.75, 0.65, -0.35));
		horn.SetScale(glm::vec3(0.2, 0.2, 0.2));
		horn.SetRotate(-40.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.SetRotate(45.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);

		horn.SetTranslate(glm::vec3(0.75, 0.65, -0.35));
		horn.SetScale(glm::vec3(0.2, 0.2, 0.2));
		horn.SetRotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		horn.SetRotate(40.0f, glm::vec3(1.0, 0.0, 0.0));
		horn.SetRotate(45.0f, glm::vec3(0.0, 0.0, 1.0));
		horn.Draw(ourShader);
		



		body.SetTranslate(glm::vec3(0, 0.0, 0));
		body.SetScale(glm::vec3(1, 1, 1));
		body.Draw(ourShader);

		eye.SetTranslate(glm::vec3(0.0, 0.6, 0.74));
		eye.SetScale(glm::vec3(0.267, 0.267, 0.267));
		eye.SetRotate(-34.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		eye.Draw(ourShader);

		mouth.SetTranslate(glm::vec3(0.0, -0.15, 0.5));
		mouth.SetScale(glm::vec3(0.7, 0.7, 0.7));
		mouth.Draw(ourShader);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &floor.VAO);
	glDeleteBuffers(1, &floor.VBO);
	glDeleteBuffers(1, &floor.EBO);

	glfwTerminate();
	return 0;
}




void getIndex(std::vector<int>& indexData, int figure) {
	int floorIndices[] = {
		0,1,2,
		2,0,3,
	};

	int teethIndices[] = {
	   0,1,2,
	   2,3,4,
	   4,5,6,
	   6,7,8,
	   8,9,10,
	   10,11,12
	};

	int hornIndices[] = {
		0,1,2,0,2,3,3,2,4,5,6,7,
		7,5,8,7,8,4,9,10,11,11,9,12,
		12,11,4,13,14,15,15,13,16,16,15,4
	};

	int bodyIndices[] = {
		0,12,1,1,12,2,2,12,13,13,2,3,3,13,4,4,13,5,
		6,14,7,7,14,8,8,14,15,15,8,9,9,15,10,10,15,11,

		16,28,17,17,28,18,18,28,29,29,18,19,19,29,20,20,29,21,
		22,30,23,23,30,24,24,30,31,31,24,25,25,31,26,26,31,27,
		27,31,16,16,31,28,28,31,30,30,28,29,29,30,22,22,29,21,

		32,44,33,33,44,34,34,44,45,34,45,35,35,45,36,36,45,46,45,46,37,36,37,46,
		37,46,38,38,46,39,39,46,40,40,46,47,40,47,41,41,47,42,42,47,43,47,44,42,
		43,44,32,44,47,46,44,45,46,44,43,42,

		48,60,49,49,60,50,50,60,61,50,61,51,51,61,52,52,61,62,62,52,53,
		53,62,54,54,62,55,55,62,56,56,62,63,56,63,57,57,63,58,58,63,60,
		58,60,59,59,60,48,60,61,62,62,63,60,


		64,76,65,65,76,66,66,76,77,66,77,67,67,77,68,68,77,78,
		78,68,69,69,78,70,70,78,71,71,78,79,79,71,72,72,79,73,
		73,79,74,74,79,76,76,74,75,75,76,64,76,77,78,78,79,76,

		80,92,81,81,92,93,93,81,82,82,93,83,83,93,84,84,93,94,
		94,84,85,85,94,86,86,94,87,87,94,95,95,87,88,88,95,89,
		89,95,90,90,95,92,92,90,91,91,92,80,92,93,94,94,95,92,

		0,97,12,12,97,98,98,12,13,13,98,5,
		5,98,99,100,101,6,6,101,14,14,101,15,
		15,101,102,102,15,103,103,15,11,96,97,0,
	};

	int eyeIndices[] = {
		0,1,2,2,1,3,3,1,4,4,3,5,5,4,6,6,5,7,7,6,8,8,6,9,0,1,10,
		10,1,11,12,1,4,4,11,13,13,4,6,6,14,15,15,6,16,16,6,9,
	};

	int mouthIndices[] = {
		0,12,1,1,12,2,2,12,13,2,13,3,3,13,4,4,13,5,
		5,13,14,5,14,6,6,14,7,7,14,8,8,14,15,8,15,9,
		9,15,10,10,15,11,11,15,12,12,11,0,12,13,14,14,15,12,
	};



	switch (figure)
	{
	case 1:
		for (int index : floorIndices) {
			indexData.push_back(index);
		}
		break;
	case 2:
		for (int index : teethIndices) {
			indexData.push_back(index);
		}
		break;
	case 3:
		for (float index : hornIndices) {
			indexData.push_back(index);
		}
		break;
	case 4:
		for (float index : bodyIndices) {
			indexData.push_back(index);
		}
		break;
	case 5:
		for (float index : eyeIndices) {
			indexData.push_back(index);
		}
		break;
	case 6:
		for (float index : mouthIndices) {
			indexData.push_back(index);
		}
		break;
	default:
		break;
	}
}

void getVertex(std::vector<float>& verticesData, int figure) {

	float floorVertices[] = {
		-0.5f, 0.0f, -0.5f,  0.0f, 20.0f,
		0.5f, 0.0f, -0.5f,  20.0f, 20.0f,
		0.5f, 0.0f,  0.5f,  20.0f, 0.0f,
		-0.5f, 0.0f,  0.5f,  0.0f, 0.0f,
	};

	float teethVertices[] = {
	   -0.9f, 0.15f, 0.0f, 0.0f, 1.0f,//0
	   -0.75f, -0.05f, 0.075f, 0.0625f, 0.4f,//1
	   -0.6f, 0.15f, 0.15f, 0.14f, 1.0f,//2
	   -0.45f, -0.1f, 0.225, 0.203f, 0.0f,//3
	   -0.3f, 0.15f, 0.35f, 0.265f, 1.0f,//4
	   -0.15f, -0.2f, 0.35f, 0.375f, 0.1f,//5
	   0.0f, 0.15f, 0.35f, 0.5f, 1.0f,//6
	   0.15f, -0.2f, 0.35f, 0.5625f, 0.1f,//7
	   0.3f, 0.15f, 0.35f, 0.64f, 1.0f,//8
	   0.45f, -0.1f, 0.225f, 0.71f, 0.2f,//9
	   0.6f, 0.15f, 0.15f, 0.84f, 1.0f,//10
	   0.75f, -0.05f, 0.075f, 0.89f, 0.0f,//11
	   0.9f, 0.15f, 0.0f, 1.0f, 1.0f,//12   
	};

	float hornVertices[] = {
		-0.2f, -0.5f, 0.3f, 0.0f, 0.0f,//0
		0.3f, -0.5f, 0.3f, 1.0f, 0.0f,//1
		0.0f, 0.0f, 0.15f, 1.0f, 0.25f,//2
		-0.35, 0.0f, 0.15f, 0.0f, 0.25f,//3
		-0.05f, 0.8f, 0.0f, 0.5f, 1.0f,//4
		0.3f, -0.5f, 0.3f, 0.0f, 0.0f,//5
		0.3f, -0.5f, -0.3f, 1.0f, 0.0f,//6
		0.0f, 0.0f, -0.15f, 1.0f, 0.25f,//7
		0.0f, 0.0f, 0.15f, 0.0f, 0.25f,//8
		0.3f, -0.5f, -0.3f, 0.0f, 0.0f,//9
		-0.2f, -0.5f, -0.3f, 1.0f, 0.0f,//10
		-0.35, 0.0f, -0.15f, 1.0f, 0.25f,//11
		0.0f, 0.0f, -0.15f, 0.0f, 0.25f,//12   
		-0.2f, -0.5f, -0.3f, 0.0f, 0.0f,//13
		-0.2f, -0.5f, 0.3f, 1.0f, 0.0f,//14
		-0.35f, 0.0f, 0.15f, 1.0f, 0.25f,//15
		-0.35f, 0.0f, -0.15f, 0.0f, 0.25f,//16
	};

	float bodyVertices[] = {
		//Передняя область
	   -0.7f, -0.35f, 0.7f, 0.25f,0.417f,//0       
	   -0.65f, -0.65f, 0.6f, 0.25f, 0.333f,//1
	   -0.35f, -0.7f, 0.6f, 0.3125f, 0.333f,//2
	   0.35f, -0.7f, 0.6f, 0.4375f, 0.333f,//3
	   0.65f, -0.65f, 0.6f, 0.5f, 0.333f,//4
	   0.7f, -0.35f, 0.7f, 0.5f,0.417f,//5

	   0.7f, 0.35f, 0.7f, 0.5f,0.583f,//6
	   0.65f, 0.65f, 0.6f, 0.5f, 0.67f,//7
	   0.35f, 0.8f, 0.6f, 0.4375f, 0.67f,//8
	   -0.35f, 0.8f, 0.6f, 0.3125f, 0.67f,//9
	   -0.65f, 0.65f, 0.6f, 0.255f, 0.67f,//10
	   -0.7f, 0.35f, 0.7f, 0.25f,0.583f,//11

	   -0.3f, -0.35f, 0.9f, 0.3125f, 0.417f,//12
	   0.3f, -0.35f, 0.9f, 0.4375f, 0.417f,//13         
		0.3f, 0.35f, 0.9f, 0.4375f, 0.583f,//14 
		-0.3f, 0.35f, 0.9f, 0.3125f, 0.583f,//15 

		//Дальняя область
	   -0.7f, -0.35f, -0.7f, 0.75f,0.417f,//16     
	   -0.65f, -0.65f, -0.6f, 0.75f, 0.34f,//17
	   -0.4f, -0.7f, -0.6f, 0.8125f, 0.34f,//18
	   0.4f, -0.7f, -0.6f, 0.9375f, 0.34f,//19
	   0.65f, -0.65f, -0.6f, 1.0f, 0.34f,//20
	   0.7f, -0.35f, -0.7f, 1.0f,0.417f,//21

	   0.7f, 0.35f, -0.7f, 1.0f,0.583f,//22
	   0.65f, 0.65f, -0.6f, 1.0f, 0.66f,//23
	   0.4f, 0.8f, -0.6f, 0.9375f, 0.66f,//24
	   -0.4f, 0.8f, -0.6f, 0.8125f, 0.66f,//25
	   -0.65f, 0.65f, -0.6f, 0.75f, 0.66f,//26
	   -0.7f, 0.35f, -0.7f, 0.75f, 0.583f,//27

	   -0.35f, -0.35f, -0.9f, 0.8125f, 0.417f,//28
	   0.35f, -0.35f, -0.9f, 0.9375f, 0.417f,//29
	   0.35f, 0.35f, -0.9f, 0.9375f, 0.56f,//30
	   -0.35f, 0.35f, -0.9f, 0.8125f, 0.56f,//31

		//Низ
	   -0.65f, -0.65f, -0.6f, 0.5f, 0.0f,//32
	   -0.4f, -0.7f, -0.6f, 0.4375f, 0.0f,//33
	   0.4f, -0.7f, -0.6f, 0.3125f, 0.0f,//34
	   0.65f, -0.65f, -0.6f, 0.255f, 0.0f,//35
	   0.65f, -0.8f, -0.2f, 0.255f, 0.13,//36
	   0.65f, -0.8f, 0.2f, 0.255f, 0.222,//37
	   0.65f, -0.65f, 0.6f, 0.255f, 0.333f,//38
	   0.35f, -0.7f, 0.6f, 0.3125f, 0.333f,//39
	   -0.35f, -0.7f, 0.6f, 0.4375f, 0.333f,//40
	   -0.65f, -0.65f, 0.6f, 0.495f, 0.333f,//41
	   -0.65f, -0.8f, 0.2f, 0.495f, 0.222,//42
	   -0.65f, -0.8f, -0.2f,0.495f,0.3,//43

	   -0.3f, -0.9f, -0.2f,0.41f, 0.13f,//44
	   0.3f, -0.9, -0.2f, 0.33f,0.13f,//45
	   0.3f, -0.9f, 0.2f,0.33f,0.222f,//46
	   -0.3f, -0.9f, 0.2f,0.41f,0.222f,//47

	   //Верх 
		-0.65f, 0.65f, -0.6f, 0.255f, 1.0f,//48
	   -0.4f, 0.8f, -0.6f, 0.3125f, 1.0f,//49
	   0.4f, 0.8f, -0.6f, 0.4375f, 1.0f,//50
	   0.65f, 0.65f, -0.6f, 0.495f, 1.0f,//51
	   0.65f, 0.8f, -0.2f, 0.495f, 0.888,//52
	   0.65f, 0.8f, 0.2f, 0.495f, 0.777,//53
	   0.65f, 0.65f, 0.6f, 0.495f, 0.67f,//54
	   0.35f, 0.8f, 0.6f, 0.4375f, 0.67f,//55
	   -0.35f, 0.8f, 0.6f, 0.3125f, 0.67f,//56
	   -0.65f, 0.65f, 0.6f, 0.255f, 0.67f,//57
	   -0.65f, 0.8f, 0.2f, 0.255f, 0.777,//58
	   -0.65f, 0.8f, -0.2f,0.255f,0.888,//59

	   -0.3f, 0.9f, -0.2f,0.33f, 0.89f,//60
	   0.3f, 0.9, -0.2f, 0.41f,0.899f,//61
	   0.3f, 0.9f, 0.2f,0.41f,0.788f,//62
	   -0.3f, 0.9f, 0.2f,0.33f,0.788f,//63


	   //Левый бок
	   -0.65f, -0.65f, 0.6f, 0.24f, 0.34f,//64
	   -0.7f, -0.35f, 0.7f, 0.25f,0.417f,//65   
	   -0.7f, 0.35f, 0.7f, 0.25f,0.583f,//66
	   -0.65f, 0.65f, 0.6f, 0.25f, 0.66f,//67

	   -0.65f, 0.8f, 0.2f, 0.171f, 0.66f,//68
	   -0.65f, 0.8f, -0.2f,0.086f,0.66f,//69

	   -0.65f, 0.65f, -0.6f, 0.0f, 0.66f,//70
	   -0.7f, 0.35f, -0.7f, 0.0f, 0.583f,//71
	   -0.7f, -0.35f, -0.7f, 0.0f, 0.417f,//72
	   -0.65f, -0.65f, -0.6f, 0.05f, 0.34f,//73

	   -0.65f, -0.8f, -0.2f, 0.086f, 0.34f,//74
	   -0.65f, -0.8f, 0.2f, 0.171f, 0.34f,//75

	   -0.8f, -0.35f, 0.2f, 0.171f, 0.425f,//76
	   -0.8f, 0.35f, 0.2f, 0.171f, 0.56f,//77
	   -0.8f, 0.35f, -0.2f, 0.086f, 0.56f,//78
	   -0.8f, -0.35f, -0.2f, 0.086f, 0.425f,//79

		//Правый бок
		0.65f, -0.65f, 0.6f, 0.24f, 0.34f,//80
		0.7f, -0.35f, 0.7f, 0.25f,0.417f,//81  
		0.7f, 0.35f, 0.7f, 0.25f,0.583f,//82
		0.65f, 0.65f, 0.6f, 0.25f, 0.66f,//83

		0.65f, 0.8f, 0.2f, 0.171f, 0.66f,//84
		0.65f, 0.8f, -0.2f,0.086f,0.66f,//85

		0.65f, 0.65f, -0.6f, 0.0f, 0.66f,//86
		0.7f, 0.35f, -0.7f, 0.0f, 0.583f,//87
		0.7f, -0.35f, -0.7f, 0.0f, 0.417f,//88
		0.65f, -0.65f, -0.6f, 0.05f, 0.34f,//89

		0.65f, -0.8f, -0.2f, 0.086f, 0.34f,//90
		0.65f, -0.8f, 0.2f, 0.171f, 0.34f,//91

		0.8f, -0.35f, 0.2f, 0.171f, 0.425f,//92
		0.8f, 0.35f, 0.2f, 0.171f, 0.56f,//93
		0.8f, 0.35f, -0.2f, 0.086f, 0.56f,//94
		0.8f, -0.35f, -0.2f, 0.086f, 0.425f,//95

		//Рот
		-0.7f, -0.05f, 0.7f,0.25f,0.47f,//96
		-0.3f, -0.3f, 0.9f,0.3125f,0.48f,//97
		0.3f, -0.3f, 0.9f,0.4375f,0.48f,//98
		0.7f, -0.05f, 0.7f,0.5f,0.47f,//99
		0.7f, 0.05f, 0.7f,0.5f,0.51f,//100
		0.3f, 0.1f, 0.9f,0.4375f,0.465f,//101
		-0.3f, 0.1f, 0.9f,0.3125f,0.465f,//102          
		-0.7f, 0.05f, 0.7f,0.25f,0.51f,//103
	};

	float eyeVertices[] = {
	 0.0f, -1.0f, 0.0f, 0.5f, 0.0f,//0
	 0.0f, -0.4f, 0.45f, 0.5f, 0.25f,//1
	 0.8f, -0.75f, 0.0f, 1.0f, 0.0f,//2    
	 0.9f, -0.25, 0.0f, 1.0f, 0.37f,//3   
	 0.0f, 0.0f, 0.5f, 0.5f, 0.5f,//4   
	 1.0f, 0.0f, 0.0f, 1.0f, 0.5f,//5    
	 0.0f, 0.4f, 0.45f, 0.5f, 0.79f,//6    
	 0.9f, 0.25, 0.0f, 1.0f, 0.63f,//7   
	 0.8f, 0.75f, 0.0f, 1.0f, 1.0f,//8   
	 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,//9  
	 -0.8f, -0.75f, 0.0f, 0.0f, 0.0f,//10    
	 -0.9f, -0.25, 0.0f, 0.0f, 0.37f,//11
	 -0.9f, -0.25, 0.0f, 1.0f, 0.37f,//12
	 -1.0f, 0.0f, 0.0f, 0.0f, 0.5f,//13
	 -1.0f, 0.0f, 0.0f, 1.0f, 0.5f,//14
	 -0.9f, 0.25, 0.0f, 1.0f, 0.63f,//15
	 -0.8f, 0.75f, 0.0f, 1.0f, 1.0f,//16            
	};

	float mouthVertices[] = {
	 -0.3f, -0.6f, 0.0f, 0.33f, 0.0f,//0
	 -0.6f, -0.55f, 0.0f,0.0f,0.0f,//1
	 -1.0f, -0.3f, 0.0f, 0.0f,0.33f,//2
	 -1.0f, 0.3f, 0.0f, 0.0f,0.67f,//3
	 -0.7f, 0.75f, 0.0f,0.0f,1.0f,//4
	 -0.3f, 0.9f, 0.0f, 0.33f,1.0f,//5
	 0.3f, 0.9f, 0.0f,0.67f,1.0f,//6
	 0.7f, 0.75f, 0.0f,1.0f,1.0f,//7
	 1.0f, 0.3f, 0.0f,1.0f,0.67f,//8
	 1.0f, -0.3f, 0.0f, 1.0f,0.33f,//9
	 0.6f, -0.55f, 0.0f, 1.0f,0.0f,//10
	 0.3f, -0.6f, 0.0f, 0.67f , 0.0f,//11
	 -0.3f,-0.3f,-0.9f, 0.33f, 0.33f, //12
	 -0.3f,0.4f,-0.9f, 0.3f, 0.65f,//13
	 0.3f,0.4f,-0.9f,0.68f,0.65f,//14
	 0.3f,-0.3f,-0.9f,0.67f,0.33f,//15
	};




	switch (figure)
	{
	case 1:
		for (float vertex : floorVertices) {
			verticesData.push_back(vertex);
		}
		break;
	case 2:
		for (float vertex : teethVertices) {
			verticesData.push_back(vertex);
		}
		break;
	case 3:
		for (float vertex : hornVertices) {
			verticesData.push_back(vertex);
		}
		break;
	case 4:
		for (float vertex : bodyVertices) {
			verticesData.push_back(vertex);
		}
		break;
	case 5:
		for (float vertex : eyeVertices) {
			verticesData.push_back(vertex);
		}
		break;
	case 6:
		for (float vertex : mouthVertices) {
			verticesData.push_back(vertex);
		}
		break;
	default:
		break;
	}


}



void SetView(int width, int height, Shader& ourShader)
{
	glm::mat4 view;
	view = camera.GetViewMatrix();
	glm::mat4 projection;
	projection = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 1000.0f);

	GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
	GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void ListenEvents()
{
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glfwPollEvents();
	Do_Movement();
}

void Do_Movement()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}