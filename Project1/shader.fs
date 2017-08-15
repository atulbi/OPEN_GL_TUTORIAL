#version 330 core
out vec4 FragColor;
in vec3 changing_color;
void main()
{
    FragColor = vec4(changing_color , 1.0f);
} 