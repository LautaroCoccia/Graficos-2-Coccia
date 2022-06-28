#version 330 core

uniform sampler2D ourTexture;

uniform vec3 lightColor;
uniform vec3 lightPos;

in vec4 outColor;
in vec2 TexCoord;

in vec3 FragPos;
in vec3 Normal;
void main()
{
	//float ambientStrength = 1.0f;
	//vec3 ambient = ambientStrength * lightColor;
	//vec3 norm = normalize(Normal);
	////
	//vec3 lightDir = normalize(lightPos - FragPos);
	//float diff = max(dot(norm, lightDir), 0.0);
	////
	//vec3 diffuse = diff * lightColor;
	////vec3 result = (ambient + diffuse) * outColor;
	//vec3 result = (diffuse * lightColor);
	//gl_FragColor = texture(ourTexture, TexCoord) * (result,1.0));
	//gl_FragColor = texture(ourTexture, TexCoord) * (outColor * vec4(lightColor + diffuse,1.0));
	gl_FragColor = texture(ourTexture, TexCoord) * (outColor *vec4(lightColor ,1.0));
}