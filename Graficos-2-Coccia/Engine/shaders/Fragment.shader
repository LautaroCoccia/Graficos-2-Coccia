#version 330 core

uniform sampler2D ourTexture;

in vec4 outColor;
in vec2 TexCoord;

struct Light
{
	vec3 color;
	vec3 ambient;
};

uniform vec3 lightColor;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	gl_FragColor = texture(ourTexture, TexCoord) * (outColor * vec4(ambient,1.0));
}