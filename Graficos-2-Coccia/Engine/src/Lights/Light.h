#ifndef LIGHT_H
#define LIGHT_H

#include "../Export/Export.h"
#include "../Renderer/Renderer.h"

namespace Engine
{
	class EXPORT_API Light
	{
	private:
		struct ambient
		{
			glm::vec3 color;
			float strength;
		};
		ambient _ambient;
		Renderer* _renderer;
		unsigned int _vao; // Vertex Array Obj
		unsigned int _vbo; // Vertex Buffer Obj
		unsigned int _ebo; // Index Buffer Obj

	public:
		Light(Renderer* renderer);
		~Light();
		void Draw();
	};
}
#endif