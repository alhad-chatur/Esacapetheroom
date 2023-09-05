
#version 330 core
out vec4 FragColor;
in vec3 ournormal;
in vec3 FragPos;  
in vec2 texcoords;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightpos;
uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    sampler2D texture1;
    sampler2D texture2;
    sampler2D texture3;
    float shininess;
}; 
uniform Material material;
  
  struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;

};

uniform Light light; 

uniform float texcoordmult;
uniform int dark;
uniform vec3 laserpos;
uniform vec3 lasercolor;

void main()
{



     float distance    = length(lightpos - FragPos);
     float attenuation = 1.0 / (light.constant + light.linear * distance + 
    		    light.quadratic * (distance * distance));    
    
    vec3 norm = normalize(ournormal);
    vec3 lightDir = normalize(lightpos - FragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
   
    vec3 diffuse = texture(material.texture1,texcoords*texcoordmult).rgb * light.diffuse*diff;

	vec3 ambient = light.ambient * vec3(texture(material.texture1, texcoords*texcoordmult));

	vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

	
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = (texture(material.texture2,texcoords*texcoordmult).rgb)* spec * light.specular;  

   vec3 emission = texture(material.texture3,texcoords*texcoordmult).rgb;

   vec3 lasercircle =vec3(0.0f);
   if(length(FragPos - laserpos) <= 0.1f)
   {
   lasercircle = vec3(0.0f,0.0f,1.0f);
   }
   if(dark ==1)
   {
    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation;   
     }
   vec3 result =ambient+diffuse+specular+emission+lasercircle;
	FragColor = vec4(result,1.0f);
}