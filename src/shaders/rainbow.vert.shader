#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 texCoord;

uniform mat4 transformation;
void main()
{
   gl_Position = transformation * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   outColor = aColor;
   texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
