#version 330 core

in vec3 objColor;
out vec4 FragColor;

void main()
{
   FragColor = vec4(objColor, 1.0);
}
