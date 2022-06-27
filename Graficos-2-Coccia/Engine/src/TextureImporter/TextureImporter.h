#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "..\Export\Export.h"
#include "..\Renderer\Renderer.h"

namespace Engine
{
	struct TextureData
	{
		unsigned char* _data;
		int _width;
		int _height;
		int _nrChannels;
		unsigned int _texture;
	};
	class EXPORT_API TextureImporter
	{

	public:

		//void ImportTexture(Renderer* renderer, const char* name, unsigned int& texture);
		static TextureData ImportTexture(Renderer* renderer,const char* filePath);
		static void BindTexture(unsigned int& texture);
	};
}

#endif