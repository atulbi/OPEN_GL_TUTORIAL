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
	float x[3600];
	float y[3600];
}CIRCLE;


CIRCLE circle;
void createcircle(float k, float r, float h) {
	float angle = 0.0f;
	for (int i = 0; i < 3600; i++)
	{
		circle.x[i] = r * cos(angle) - h;
		circle.y[i] = r * sin(angle) + k;
		angle = angle + 0.1f;
		
	}
}

void GiveLineVertex(double a[], double start, double length )
{
	int k = 0;
	for ( double i = 0; i <360;)
	{
		a[k++] = start * cos(i);
		a[k++] = start *sin(i);
		a[k++] = 0.0f;
		a[k++] = (start+length) * cos(i);
		a[k++] = (start + length) *sin(i);
		a[k++] = 0.0f;

		i = i + (double)30;

	}
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Window01", NULL, NULL);

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
	glViewport(0, 0, 800, 800);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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

	float vertices[21600] ;

	double line_array[72];

	GiveLineVertex(line_array, 0.650, 0.075);
	
	createcircle(0.0f, 0.75f, 0.0f);

	int j = 0;
	for (int i = 0; i < 3600; i++)
	{
		vertices[j++] = circle.x[i];
		vertices[j++] = circle.y[i];
		vertices[j++] = 0.0f;
	}

	createcircle(0.0f, 0.725f, 0.0f);
	for (int i = 0; i < 3600; i++)
	{
		vertices[j++] = circle.x[i];
		vertices[j++] = circle.y[i];
		vertices[j++] = 0.0f;
	}

	std::cout << "last :" << j << std::endl;

	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VBO_LINES;
	glGenBuffers(1, &VBO_LINES);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_LINES);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_array), line_array, GL_STATIC_DRAW);

	GLuint VertexArrayID[3];
	glGenVertexArrays(3, VertexArrayID);

	glBindVertexArray(VertexArrayID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	


	glBindVertexArray(VertexArrayID[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3600*sizeof(float)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(VertexArrayID[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_LINES);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);
	
	


	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(20.0);
		glLineWidth(70.0);
		glBindVertexArray(VertexArrayID[0]);
		glUseProgram(shaderProgram[0]);
		glDrawArrays(GL_LINE_STRIP, 0, 3600);

		glPointSize(15.0);
		glLineWidth(40.0);

		glBindVertexArray(VertexArrayID[1]);
		glUseProgram(shaderProgram[1]);
		glDrawArrays(GL_LINES, 3600,3600);

		glBindVertexArray(VertexArrayID[2]);
		glUseProgram(shaderProgram[1]);
		glDrawArrays(GL_LINES, 0, 72);

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			return 0;
		}
	}
	return 0;

}

