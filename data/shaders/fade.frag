#version 330 core

out vec4 FragColor;

uniform float alpha = 1.0;

void main() 
{
    FragColor = vec4(0.0, 0.0, 0.0, alpha);
}
