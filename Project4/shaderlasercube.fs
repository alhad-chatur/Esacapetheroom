
#version 330 core
out vec4 FragColor;
in vec2 texcoords;
in vec3 FragPos; 
flat in int index;

uniform sampler2D texture1;

void main()
{   
   vec4 texColor;
    texColor = texture(texture1, texcoords);

   // if(texColor.a < 0.1)
   //     discard;
    FragColor = texColor;
}