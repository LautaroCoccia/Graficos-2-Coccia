#version 330 core

uniform sampler2D ourTexture;

in vec2 TexCoord;

void main()
{
	vec4 texColor = texture(ourTexture, TexCoord);
	if (texColor.a < 0.1)
		discard;
	gl_FragColor = texture(ourTexture, TexCoord);
}