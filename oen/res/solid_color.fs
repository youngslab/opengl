#version 330 core

out vec4 FragColor;

uniform vec3 u_color;

void main()
{
   FragColor = u_color;
}

