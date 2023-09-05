 #version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 atexcoord;
out vec2 texcoord;

uniform mat4 change;

void main()
{
   vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);
  pos = pos*change;
   gl_Position =pos;
   texcoord = atexcoord;
};