#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexNum;
layout (location = 4) in vec3 aNormal;

out vec2 vTexCoord;
out float vTexNum;
out vec3 vNormal;
out vec3 vPos;

uniform mat4 transformation;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vPos = vec3(transformation * vec4(aPos, 1.0));
    vNormal = mat3(transpose(inverse(transformation))) * aNormal;
    gl_Position = projection * view * vec4(vPos, 1.0);
    vTexCoord = aTexCoord;
    vTexNum = aTexNum;
}
