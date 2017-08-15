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
	float x;
	float y;
}CIRCLE;

CIRCLE circle;
void createcircle(int k, int r, int h) {
	for (int i = 0; i < 180; i++)
	{
		circle.x = r * cos(i) - h;
		circle.y = r * sin(i) + k;
		glVertex3f(circle.x + k, circle.y - h, 0);

		circle.x = r * cos(i + 0.1) - h;
		circle.y = r * sin(i + 0.1) + k;
		glVertex3f(circle.x + k, circle.y - h, 0);
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

	float vertices[] = {
		-1.0f,0.0f,0.0f,	1.0f , 0.2f ,0.3f ,
		0.0f,1.0f,0.0f,		0.f , 1.0f , 0.0f,
		1.0f,0.0f,0.0f,		0.0f , 0.0f , 1.0f,
		0.0f,-1.0f,0.0f	,	0.0f , 1.0f , 0.0f,
	};
	unsigned int indices1[] = {  // note that we start from 0!
		0,1,2// first triangle
			 // second triangle
	};

	unsigned int indices2[] = {  // note that we start from 0!
		0,2,3// first triangle
			 // second triangle
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO1;
	glGenBuffers(1, &EBO1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	unsigned int EBO2;
	glGenBuffers(1, &EBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);


	GLuint VertexArrayID[2];
	glGenVertexArrays(2, VertexArrayID);

	glBindVertexArray(VertexArrayID[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VertexArrayID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VertexArrayID[0]);
		glUseProgram(shaderProgram[0]);
		/*
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram[0], "changing_color");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(VertexArrayID[1]);
		glUseProgram(shaderProgram[1]);
		/*
		glBindVertexArray(VertexArrayID[1]);
		glUseProgram(shaderProgram[1]);
		timeValue = glfwGetTime();
		greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		vertexColorLocation = glGetUniformLocation(shaderProgram[1], "changing_color");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		*/
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

