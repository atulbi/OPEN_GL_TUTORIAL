#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>
#include<glad\glad.h>
#include <GL/glfw3.h>


#include "fragment_shader_loader.hpp"

GLuint LoadFragmentShader(const char * fragment_file_path) {

	// Read the Vertex Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment_file_path);
		getchar();
	}

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	const char* FragmentSourcePointer;
	FragmentSourcePointer = FragmentShaderCode.c_str();

	cout << FragmentSourcePointer << endl;

	unsigned int framentShader;
	framentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(framentShader, 1, &FragmentSourcePointer, NULL);
	glCompileShader(framentShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(framentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(framentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return framentShader;

}


