
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location =1) in vec3 anormal;
layout (location =2) in vec2 atexcoords;

out vec3 FragPos;  
out vec3 OurColor;
out vec3 ournormal;
out vec2 texcoords;
flat out int index;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal1;
uniform float time;


void main()
{
	 vec3 pos = aPos;
	 index = gl_VertexID;
	 pos.x = pos.x +(sin(time)*0.005);
	 pos.y = pos.y +(cos(time)*0.005);

	 gl_Position = projection * view * model * vec4(pos, 1.0);
	 ournormal = normal1*anormal;
	 FragPos = vec3(model * vec4(aPos, 1.0));
	
	 texcoords =atexcoords;
}