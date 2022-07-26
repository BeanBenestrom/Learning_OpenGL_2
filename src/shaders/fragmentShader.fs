#version 430 core
out vec4 FragColor;


in vec2 texCoord;

uniform vec3 color;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(color * lightColor, 1);
} 