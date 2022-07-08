#version 330 core
out vec4 FragColor;


in vec2 texCoord;
in vec3 color;

uniform sampler2D tex0;
// uniform float mixAmount;

void main()
{
    FragColor = texture(tex0, texCoord);
} 