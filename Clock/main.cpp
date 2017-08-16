// Include standard headers
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include <stdlib.h>
#include<math.h>
#include<glad\glad.h>
#include <GL/glfw3.h>
#include<string>
#include<string.h>
#include"vertex_shader_loader.hpp"
#include"fragment_shader_loader.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
typedef struct
{
	float x[180];
	float y[180];
}CIRCLE;

CIRCLE circle;
void createcircle(float k, float r, float h) {
	for (int i = 0; i < 180; i++)
	{
		circle.x[i] = r * cos(i) - h;
		circle.y[i] = r * sin(i) + k;
		
	}
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Window01", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed in creating window " << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 1920, 1080);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.3f, 0.4f, 0.7f, 0.9f);

	GLuint vertexID = LoadVertexShader("shader.vs");
	GLuint fragmentID = LoadFragmentShader("shader.fs");
	GLuint frgamentID2 = LoadFragmentShader("fshader2.fs");

	unsigned int shaderProgram[2];

	shaderProgram[0] = glCreateProgram();
	glAttachShader(shaderProgram[0], vertexID);
	glAttachShader(shaderProgram[0], fragmentID);
	glLinkProgram(shaderProgram[0]);


	shaderProgram[1] = glCreateProgram();
	glAttachShader(shaderProgram[1], vertexID);
	glAttachShader(shaderProgram[1], frgamentID2);
	glLinkProgram(shaderProgram[1]);


	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::lINKING::LINKER_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	float vertices[1080] ;
	
	createcircle(0.0f, 0.5f, 0.0f);

	int j = 0;
	for (int i = 0; i < 180; i++)
	{
		vertices[j++] = circle.x[i];
		vertices[j++] = circle.y[i];
		vertices[j++] = 0.0f;
	}

	createcircle(0.0f, 0.3f, 0.0f);
	for (int i = 0; i < 180; i++)
	{
		vertices[j++] = circle.x[i];
		vertices[j++] = circle.y[i];
		vertices[j++] = 0.0f;
	}

	std::cout << "last :" << j << std::endl;

	unsigned int indices1[] = {  // note that we start from 0!
		0,1,2
	};

	unsigned int indices2[] = {  // note that we start from 0!
		0,2,3
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	GLuint VertexArrayID[2];
	glGenVertexArrays(2, VertexArrayID);

	glBindVertexArray(VertexArrayID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 180, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	


	glBindVertexArray(VertexArrayID[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(180*sizeof(float)));
	glEnableVertexAttribArray(0);
	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VertexArrayID[0]);
		glUseProgram(shaderProgram[0]);
		

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(VertexArrayID[1]);
		glUseProgram(shaderProgram[1]);
		
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			return 0;
		}
	}
	return 0;

}

