#include "TextureImporter.h"

#include "GL\glew.h"
#include "glm\glm.hpp"

//#define STB_IMAGE_IMPLEMENTATION
#include "..\TextureImporter\stb_image.h"

#include <iostream>

using namespace std;

namespace Engine
{
	

	/*void TextureImporter::ImportTexture(Renderer* renderer, const char* name, unsigned int& texture)
	{
		stbi_set_flip_vertically_on_load(true);

		_textureData._data = stbi_load(name, &_textureData._width, &_textureData._height, &_textureData._nrChannels, 0);

		if (!_textureData._data)
		{
			cout << "failed to load texture" << endl;
			return;
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (_textureData._nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _textureData._width, _textureData._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _textureData._data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _textureData._width, _textureData._height, 0, GL_RGB, GL_UNSIGNED_BYTE, _textureData._data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(_textureData._data);

		glUseProgram(renderer->GetShader());
		glUniform1i(glGetUniformLocation(renderer->GetShader(), "ourTexture"), 0);
	}*/
	TextureData TextureImporter::ImportTexture(Renderer* renderer, const char* filePath)
	{
		TextureData _textureData;
		stbi_set_flip_vertically_on_load(true);

		_textureData._data = stbi_load(filePath, &_textureData._width, &_textureData._height, &_textureData._nrChannels, 0);

		if (!_textureData._data)
		{
			cout << "failed to load texture" << endl;
			
		}

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (_textureData._nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _textureData._width, _textureData._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _textureData._data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _textureData._width, _textureData._height, 0, GL_RGB, GL_UNSIGNED_BYTE, _textureData._data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(_textureData._data);

		glUseProgram(renderer->GetShader());
		glUniform1i(glGetUniformLocation(renderer->GetShader(), "ourTexture"), 0);
		return _textureData;
	}
	void TextureImporter::BindTexture(unsigned int& texture)
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
}