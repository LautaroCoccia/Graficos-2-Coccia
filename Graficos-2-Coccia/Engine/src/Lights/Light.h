#ifndef LIGHT_H
#define LIGHT_H

#include "../Export/Export.h"
#include "../Renderer/Renderer.h"

namespace Engine
{
	class EXPORT_API Light : public Entity
	{
	private:
		glm::vec3 _lightColor;
		float _ambientStrength;
		Renderer* _renderer;
		unsigned int _vao; // Vertex Array Obj
		unsigned int _vbo; // Vertex Buffer Obj
		unsigned int _ebo; // Index Buffer Obj

	public:
		Light(Renderer* renderer);
		~Light();
		void SetLightColor(glm::vec3 lightColor, float ambientStrength);
		void Draw();
		void TriggerCollision(Entity* other) override;
	};
}
#endif