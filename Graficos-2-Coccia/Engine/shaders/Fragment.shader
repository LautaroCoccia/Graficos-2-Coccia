#version 330 core

uniform sampler2D ourTexture;

in vec4 outColor;
in vec2 TexCoord;


void main()
{
	gl_FragColor = texture(ourTexture, TexCoord) *outColor;
}