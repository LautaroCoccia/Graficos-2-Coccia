#include "Cubo.h"

namespace Engine
{
	Cubo::Cubo(const char* filePath, Renderer* renderer) : Entity()
	{
		_renderer = renderer;
        _vertexSize = sizeof(_vertices);

		_renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

		_renderer->SetCubeVertexAttribPointer(_modelUniform);
		
        TI.ImportTexture(_renderer, filePath, _diffuse);
		if (_diffuse._nrChannels == 4)
            _diffuse._alpha = true;

        TI.ImportTexture(_renderer, filePath, _specular);
        if (_specular._nrChannels == 4)
            _specular._alpha = true;
		
        _renderer->BindTextures(_diffuseTexture, _specularTexture);
//        _renderer->BindTexture(_diffuse._texture);
//
//        _renderer->BindTexture(_specular._texture);
        //-------------------------------



        _material._ambient = glm::vec3(1.0, 1.0, 1.0);
        _material._diffuse = glm::vec3(1, 1, 1);
        _material._specular = glm::vec3(0.1, 0.1f, 0.1f);
        _material._shininess = 32;
	}

    Cubo::Cubo(const char* diffuse, const char* specular, Renderer* renderer) : Entity()
    {
        _renderer = renderer;

        
        _renderer->BindTextures(_diffuseTexture, _specularTexture);
        _material._ambient = glm::vec3(1.0, 1.0, 1.0);
        _material._diffuse = glm::vec3(1, 1, 1);
        _material._specular = glm::vec3(0.1, 0.1f, 0.1f);
        _material._shininess = 32;

        _vertexSize = sizeof(_vertices);

        _renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
        _renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

        _renderer->SetCubeVertexAttribPointer(_modelUniform);
        

            TI.ImportTexture(_renderer, diffuse, _diffuseTexture);
        if (specular != NULL)
            TI.ImportTexture(_renderer, specular, _specularTexture);
        else
            TI.ImportTexture(_renderer, diffuse, _specularTexture);

        _renderer->BindTextures(_diffuseTexture, _specularTexture);

        //-------------------------------



        
    }
    /*Cubo::Cubo(const char* filePath, Renderer* renderer) : Entity()
    {
        _renderer = renderer;

        TI.ImportTexture(_renderer, filePath, _data);
        if (_data._nrChannels == 4)
            _alpha = true;

        _vertexSize = sizeof(_vertices);

        //_renderer->CreateBuffers();
        //_renderer->BindBuffers();

        _renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
        _renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

        _renderer->SetCubeVertexAttribPointer(_modelUniform);
        _renderer->BindTexture(_data._diffuse);
        //_renderer->SetVertexAttribPointer(false, _modelUniform);

        //material.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
        //material.ambient = glm::vec3(1.0, 1.0, 1.0);
        //material.diffuse = glm::vec3(1.0, 1.0, 1.0);
        //material.shininess = 1;
        //material.specular = glm::vec3(1.0, 1.0, 1.0);

        _material._ambient = glm::vec3(1.0, 1.0, 1.0);
        _material._diffuse = glm::vec3(1, 1, 1);
        _material._specular = glm::vec3(0.1, 0.1f, 0.1f);
        _material._shininess = 32;
    }*/
    void Cubo::SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    {
        _material._ambient = ambient;
        _material._diffuse = diffuse;
        _material._specular = specular;
        _material._shininess = shininess;

        _renderer->UpdateMaterial(_material);
        //glm::vec3 ambient = glm::vec3(1, 1, 1);
        //glm::vec3 diffuse = glm::vec3(0.1, 0.5f, 0.31f);
        //glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
        //float shininess = 256;
    }
	void Cubo::Draw()
	{
        //_renderer->UpdateMaterial(_material);
		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);
		_renderer->SetCubeVertexAttribPointer(_modelUniform);

		//_renderer->BindTextures(_diffuse._texture, _specular._texture);
		_renderer->BindTexture(_diffuse._texture);

		_renderer->Draw(_diffuse._alpha,_vao, _vbo, _ebo, _vertices, _vertexSize, sizeof(_index) / sizeof(float));
		
		_renderer->DisableTexture();
	}
	void Cubo::TriggerCollision(Entity* other) { }

}