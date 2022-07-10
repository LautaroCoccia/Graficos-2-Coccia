#version 330 core

uniform sampler2D ourTexture;

in vec3 FragPos;
in vec4 outColor;
in vec2 TexCoords;
in vec3 Normal; // Light

struct Ambient
{
	vec3 color;
	float strength;
};
uniform Ambient ambient;
uniform vec3 objectColor;

void main()
{
	vec3 ambient = ambient.color * ambient.strength;
	gl_FragColor = texture(ourTexture, TexCoords) * (outColor * vec4(ambient,1.0));
}