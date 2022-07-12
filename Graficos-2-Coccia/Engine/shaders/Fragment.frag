#version 330 core
out vec3 FragColor;

uniform sampler2D ourTexture;

in vec3 FragPos;
//in vec4 outColor;
in vec2 TexCoords;
in vec3 Normal; //Light

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  

uniform vec3 viewPos; 
//uniform vec3 lightPos; 
//uniform vec3 lightColor; // color + ambient
uniform vec3 objectColor;

void main()
{
	//vec3 ambient = ambient.color * ambient.strength;
	//gl_FragColor = texture(ourTexture, TexCoords) * (outColor * vec4(ambient,1.0));

	//vec3 ambient = light.ambient * material.ambient;
	//
    //// diffuse 
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * (diff * material.diffuse);
    //
    //// specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  
    //
    ////vec3 result = (ambient + diffuse) * objectColor;
    //vec3 result = (ambient + diffuse + specular);
	//gl_FragColor = texture(ourTexture, TexCoords) * (outColor * vec4(result,1.0));
	//FragColor= texture(ourTexture, TexCoords) * (outColor * vec4(lightColor,1.0));
   
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    gl_FragColor = vec4(result, 1.0);
}