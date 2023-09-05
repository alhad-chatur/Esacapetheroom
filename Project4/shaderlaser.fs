#version 330 core
in vec3 FragPos; 
out vec4 FragColor;

uniform vec3 lightcolor;

void main()
{
   FragColor = vec4(0.0f,1.0f,0.0f,1.0f); 
}