#include "Model.h"

namespace Engine
{

	Model::Model(Renderer* rend, string const& path, bool flipUVs, bool gamma) : gammaCorrection(gamma)
	{
		_model.renderer = rend;

		ModelImporter::loadModel(path, flipUVs, _model);
	}

	void Model::Draw()
	{
		_model.renderer->UpdateProgram(TRS);
		for (unsigned int i = 0; i < _model.meshes.size(); i++)
		{
			_model.meshes[i].Draw();
		}
	}
	void Model::TriggerCollision(Entity* other) { }

}
