#version 330 core

uniform mat4 mvp = mat4(1.0);

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec3 color;

void main()
{
    color = aColor;
    gl_Position = mvp * vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
}
