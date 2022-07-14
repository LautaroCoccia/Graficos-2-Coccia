#ifndef MODEL_H
#define MODEL_H

//#include <glm/glm.hpp>

#include "../Entity/Entity.h"
#include "../Export/Export.h"
#include "../ModelImporter/ModelImporter.h"
#include "../Renderer/Renderer.h"
#include "../3D/Mesh.h"

using namespace std;

namespace Engine
{
	class EXPORT_API Model : public Entity
	{
	private:
		bool gammaCorrection;
	public:
		Model(Renderer* rend, string const& path, bool flipUVs, bool gamma);

		ModelData _model;

		void Draw();
		void TriggerCollision(Entity* other);
	};
}
#endif 