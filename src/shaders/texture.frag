#version 330 core
out vec4 FragColor;
  
in vec2 vTexCoord;
in float vTexNum;
in vec3 vPos;
in vec3 vNormal;

uniform sampler2D uTexture[6];
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
    vec3 ambient = 0.2 * lightColor;
    
    // diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.2;
    vec3 viewDir = normalize(viewPos - vPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
        
    int index = int(vTexNum);
    vec3 result = (ambient + diffuse + specular) * vec3(texture(uTexture[index], vTexCoord));
    FragColor = vec4(result, 1.0);
}
