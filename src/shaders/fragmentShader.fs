#version 430 core
out vec4 FragColor;


in vec2 texCoord;
in vec3 FragPos;
in vec3 normal;

uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float ambientScalar;
uniform float secularScalar;
uniform float shine;

uniform vec3 camPosition;

void main()
{
    vec3 norm = normalize(normal);
    vec3 dirVector = normalize(lightPosition - FragPos);
    vec3 diffuse = max(dot(norm, dirVector), 0.0) * lightColor;

    vec3 viewDir = normalize(camPosition - FragPos);
    vec3 reflectDir = reflect(dirVector, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shine);
    vec3 secular = secularScalar * spec * lightColor;

    vec3 ambient = ambientScalar * lightColor;

    FragColor = vec4((ambient + diffuse + secular) * color, 1);
} 