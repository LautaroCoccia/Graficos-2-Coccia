#ifndef LIGHT_H
#define LIGHT_H

#include "../Export/Export.h"
#include "../Renderer/Renderer.h"

namespace Engine
{
	class EXPORT_API Light : public Entity
	{
	private:
		struct ambient
		{
			glm::vec3 color;
			float strength;
		};
		ambient _ambient;

		LightData _lightData;

		Renderer* _renderer;
		unsigned int _vao; // Vertex Array Obj
		unsigned int _vbo; // Vertex Buffer Obj
		unsigned int _ebo; // Index Buffer Obj
	public:
		Light(Renderer* renderer);
		~Light();
		void SetLightColorAmbient(glm::vec3 lightColor, float ambientStrength);
		void SetPosition(glm::vec3 position);
		void Draw();
		void TriggerCollision(Entity* other) override;
	};
}
#endif