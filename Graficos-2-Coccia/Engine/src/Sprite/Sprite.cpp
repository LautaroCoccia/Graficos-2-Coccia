#include "Sprite.h"

namespace Engine
{	
	Sprite::Sprite(Renderer* renderer) : Entity()
	{
		_renderer = renderer;
		//_textureImporter = new TextureImporter();

		_animation = new Animation();
	}

	Sprite::Sprite(Renderer* renderer, const glm::ivec2& tileDimensions) : Entity()
	{
		_renderer = renderer;
		//_textureImporter = new TextureImporter();

		_animation = new Animation();
		_animation->InitSpriteSheet(this, tileDimensions);
	}

	Sprite::~Sprite()
	{
		//_renderer->DeleteBuffers(_vao, _vbo, _ebo);

		if (_animation != NULL)
			delete _animation;
		//if (_textureImporter != NULL)
		//	delete _textureImporter;
	}

	void Sprite::InitTexture()
	{
		_vertexSize = sizeof(_vertex);

		//_renderer->CreateBuffers();
		//_renderer->BindBuffers();
		//_renderer->SetVertexSpriteAttribPointer();
		
		_renderer->SetVertexBuffer(_vertexSize, _vertex, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, _index, _ebo);
		
		_renderer->SetVertexAttribPointer(false, _modelUniform);
	}
	
	void Sprite::ImportTexture(const char* name)
	{
		//_textureImporter->ImportTexture(_renderer, name, _textureData._texture);
		_textureImporter->ImportTexture(_renderer, name, _textureData);
		if (_textureData._nrChannels == 4)
			_alpha = true;
	}
	void Sprite::CalculateNormal()
	{
		SetNormal(glm::vec3(_vertex[0], _vertex[1], _vertex[2]), glm::vec3(_vertex[9], _vertex[10], _vertex[11]),
			glm::vec3(_vertex[18], _vertex[19], _vertex[20]));
	}
	void Sprite::Draw()
	{
		_renderer->SetVertexAttribPointer(false, _modelUniform);
		
		_renderer->BindTexture(_textureData._texture);
		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);
		//_textureImporter->BindTexture(_textureData._texture);
		_renderer->Draw(_alpha,_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_index) / sizeof(float));

		_renderer->DisableTexture();
	}

	void Sprite::DrawAnimation(glm::vec4 uvRect)
	{
		//UpdateUVs
		_vertex[7] =  _uv[0].u; _vertex[8]  = _uv[0].v;
		_vertex[16] = _uv[1].u; _vertex[17] = _uv[1].v;
		_vertex[25] = _uv[2].u; _vertex[26] = _uv[2].v;
		_vertex[34] = _uv[3].u; _vertex[35] = _uv[3].v;

		//Set UV
		_uv[0].u = uvRect.x + uvRect.z; _uv[0].v = uvRect.y + uvRect.w;
		_uv[1].u = uvRect.x + uvRect.z; _uv[1].v = uvRect.y;
		_uv[2].u = uvRect.x; _uv[2].v = uvRect.y;
		_uv[3].u = uvRect.x; _uv[3].v = uvRect.y + uvRect.w;

		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);

		_renderer->BindTexture(_textureData._texture);

		_renderer->Draw(_alpha,_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_index) / sizeof(float));

		_renderer->DisableTexture();
	}
	// --------------------------------
	void Sprite::SetColor(ENTITY_COLOR color) { }

	void Sprite::SetColor(float r, float g, float b) { }

	void Sprite::TriggerCollision(Entity* other) { }

	void Sprite::SetAnimation()
	{
		_animation = new Animation(); // para el final te agregamos una lista de animaciones
	}

	Animation* Sprite::GetAnimation()
	{
		return _animation;
	}
}

