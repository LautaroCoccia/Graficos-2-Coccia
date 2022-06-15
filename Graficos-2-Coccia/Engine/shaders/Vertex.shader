#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	ourColor = aColor;
	TexCoord = aTexCoord;

	FragColor = vec4(lightColor * objectColor, 1.0);
}