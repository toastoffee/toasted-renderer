#version 330 core

out vec4 FragColor;

in vec4 localPos;

void main()
{
    FragColor = localPos;
}