#version 330 core

uniform sampler2D ourTexture;

in vec2 TexCoord;

//light
out vec4 FragColor;
uniform vec3 objectColor;
uniform vec3 lightColor;


void main()
{
	vec4 texColor = texture(ourTexture, TexCoord);
	if (texColor.a < 0.1)
		discard;

	gl_FragColor = texture(ourTexture, TexCoord);
	
	//light
	//FragColor = vec4(lightColor * objectColor * texColor.rgb, texColor.a);
	gl_FragColor = vec4(lightColor * objectColor * texColor.rgb, texColor.a);
}