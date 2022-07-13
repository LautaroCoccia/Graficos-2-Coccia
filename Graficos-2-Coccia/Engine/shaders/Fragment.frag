#version 330 core
out vec3 FragColor;

uniform sampler2D ourTexture;

in vec3 FragPos;
//in vec4 outColor;
in vec2 TexCoords;
in vec3 Normal; //Light

struct Material {
    sampler2D diffuse;
    sampler2D specular; 
    sampler2D emission; 
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

struct DirectionalLight
{
    vec3 color;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    int isActive;
};
uniform DirectionalLight _directionalLight;
uniform vec3 viewPos; 
//uniform vec3 lightPos; 
//uniform vec3 lightColor; // color + ambient
uniform vec3 objectColor;

vec4 CalculateDirectionData(vec3 normal, vec3 viewDirection);

void main()
{   vec4 resultColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(viewPos - FragPos);


    if (_directionalLight.isActive != 0)
    {
        resultColor += CalculateDirectionData(normal, viewDirection);
    }
  	
    //vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    /*// diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    
    //vec3 emission = texture(material.emission, TexCoords).rgb;
    //    
    //vec3 result = ambient + diffuse + specular + emission;
    vec3 result = ambient + diffuse + specular ;
    gl_FragColor = vec4(result, 1.0);*/

    gl_FragColor = resultColor;
}

vec4 CalculateDirectionData(vec3 normal, vec3 viewDirection)
{
    // ambient
    vec3 ambient = _directionalLight.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse
    vec3 lightDir = normalize(-_directionalLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = _directionalLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    vec3 specular = _directionalLight.specular * spec * vec3(texture(material.specular, TexCoords));

    return vec4((ambient + diffuse + specular), 1.0f);
}