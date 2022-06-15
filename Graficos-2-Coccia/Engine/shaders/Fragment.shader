#version 330 core

uniform sampler2D ourTexture;

in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	gl_FragColor = texture(ourTexture, TexCoord);
	FragColor = vec4(lightColor * objectColor, 1.0f);
}