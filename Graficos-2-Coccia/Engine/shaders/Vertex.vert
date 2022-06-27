#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aNormal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 outColor;
out vec2 TexCoord;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	outColor = aColor;
	TexCoord = aTexCoord;
	Normal = aNormal;
	//FragPos = vec3(model * vec4(aPos,1.0))
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}