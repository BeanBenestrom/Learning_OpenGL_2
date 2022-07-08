#version 330 core
out vec4 FragColor;


in vec2 texCoord;

uniform sampler2D tex0;
uniform vec4 color;
uniform int mode;           // Mode:  Color = 0   Texture = 1
// uniform float mixAmount;

void main()
{
    if (mode == 0) FragColor = color;
    else if (mode == 1) FragColor = texture(tex0, texCoord);  
} 