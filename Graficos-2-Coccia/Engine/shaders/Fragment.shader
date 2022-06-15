#version 330 core

uniform sampler2D ourTexture;

in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	gl_FragColor = texture(ourTexture, TexCoord);
	FragColor = vec4(objectColor * vec4(lightColor, 1.0f));
}