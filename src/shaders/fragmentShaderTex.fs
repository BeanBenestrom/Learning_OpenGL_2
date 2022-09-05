#version 430 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D unit;

void main()
{
    FragColor = texture(unit, texCoord);
} 