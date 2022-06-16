#version 330 core

uniform sampler2D ourTexture;

in vec4 outColor;
in vec2 TexCoord;

uniform vec3 lightColor;
void main()
{
	gl_FragColor = texture(ourTexture, TexCoord) * (outColor * vec4(lightColor,1.0));
}