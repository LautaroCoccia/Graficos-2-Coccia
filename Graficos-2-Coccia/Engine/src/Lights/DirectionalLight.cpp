#include "DirectionalLight.h"
namespace Engine
{
	DirectionalLight::DirectionalLight(Renderer* renderer, glm::vec3 color, glm::vec3 direction) : Light(renderer,color)
	{
		SetDirection(direction);
	}
	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::Draw() 
	{
		_renderer->UpdateDirectLightData(_lightData, _directionData);
	}
	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		_directionData._direction = direction;
	}
}