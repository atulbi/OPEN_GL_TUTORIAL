#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 aCol ; 
 
 out vec3 changing_color;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

	changing_color = aCol;
	
}