#include "Shape.h"
#include <iostream>

namespace Engine
{
	Shape::Shape(Renderer* renderer) : Entity()
	{
		_renderer = renderer;
	}

	Shape::~Shape()
	{
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);
	}

	void Shape::InitShape(TypeOfShape type)
	{
		_shape = type;
		
		switch (type)
		{
		case TypeOfShape::Triangle:

			_vertex = _triangleVertex;
			_vertexSize = sizeof(_triangleVertex);

			_renderer->SetVertexBuffer(_vertexSize, _vertex, _vao, _vbo);
			_renderer->SetIndexBuffer(_vertexSize, _indexTris, _ebo);
			break;

		case TypeOfShape::Quad:
			_vertex = _quadVertex;
			_vertexSize = sizeof(_quadVertex);

			_renderer->SetVertexBuffer(_vertexSize, _vertex, _vao, _vbo);
			_renderer->SetIndexBuffer(_vertexSize, _indexPos, _ebo);
			break;
		case TypeOfShape::Cube:
			_vertex = _cubeVetices;
			_vertexSize = sizeof(_cubeVetices);

			_renderer->SetVertexBuffer(_vertexSize, _vertex, _vao, _vbo);
			_renderer->SetIndexBuffer(_vertexSize, _cubeIndices, _ebo);
			break;
		}

		_renderer->SetVertexAttribPointer(true, _modelUniform);

		SetColor(ENTITY_COLOR::WHITE);
	}

	void Shape::Draw()
	{
		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);

		switch (_shape)
		{
		case TypeOfShape::Triangle:
			_renderer->Draw(_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_indexTris) / sizeof(float));
			break;

		case TypeOfShape::Quad:
			_renderer->Draw(_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_indexPos) / sizeof(float));
			break;
		case TypeOfShape::Cube:
			_renderer->Draw(_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_cubeIndices) / sizeof(float));
		}
	}

	// -------------------------------------------

	void Shape::SetColor(ENTITY_COLOR color)
	{
		switch (color)
		{
		case ENTITY_COLOR::WHITE:
			if (_shape == TypeOfShape::Triangle) 
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						_triangleVertex[3 + j * 6 + i] = 1.0f;
			}
			else if (_shape == TypeOfShape::Quad)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 4; j++)
						_quadVertex[3 + j * 6 + i] = 1.0f;
			}
			else if (_shape == TypeOfShape::Cube)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 4; j++)
						_cubeVetices[3 + j * 6 + i] = 1.0f;
			}
			break;

		case ENTITY_COLOR::BLACK:
			if (_shape == TypeOfShape::Triangle)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						_triangleVertex[3 + j * 6 + i] = 0.0f;
			}
			else if (_shape == TypeOfShape::Quad)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 4; j++)
						_quadVertex[3 + j * 6 + i] = 0.0f;
			}
			else if (_shape == TypeOfShape::Cube)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 4; j++)
						_cubeVetices[3 + j * 6 + i] = 0.0f;
			}
			break;

		case ENTITY_COLOR::GRAY:
			if (_shape == TypeOfShape::Triangle)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						_triangleVertex[3 + j * 6 + i] = 0.5f;
			}
			else if (_shape == TypeOfShape::Quad)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 4; j++)
						_quadVertex[3 + j * 6 + i] = 0.5f;
			}
			else if (_shape == TypeOfShape::Cube)
			{
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 4; j++)
						_cubeVetices[3 + j * 6 + i] = 0.5f;
			}
			break;

		case ENTITY_COLOR::RED:
			if (_shape == TypeOfShape::Triangle)
			{
				_triangleVertex[3] =  1.0f;  _triangleVertex[4] = 0.0f;  _triangleVertex[5] = 0.0f;
				_triangleVertex[9] =  1.0f; _triangleVertex[10] = 0.0f; _triangleVertex[11] = 0.0f;
				_triangleVertex[15] = 1.0f; _triangleVertex[16] = 0.0f; _triangleVertex[17] = 0.0f;
			}
			else if (_shape == TypeOfShape::Quad)
			{
				_quadVertex[3] =  1.0f;  _quadVertex[4] = 0.0f;  _quadVertex[5] = 0.0f;
				_quadVertex[9] =  1.0f; _quadVertex[10] = 0.0f; _quadVertex[11] = 0.0f;
				_quadVertex[15] = 1.0f; _quadVertex[16] = 0.0f; _quadVertex[17] = 0.0f;
				_quadVertex[21] = 1.0f; _quadVertex[22] = 0.0f; _quadVertex[23] = 0.0f;
			}
			else if (_shape == TypeOfShape::Cube)
			{
				_cubeVetices[3]  = 1.0f;  _cubeVetices[4] = 0.0f;  _cubeVetices[5] = 0.0f;
				_cubeVetices[9]  = 1.0f; _cubeVetices[10] = 0.0f; _cubeVetices[11] = 0.0f;
				_cubeVetices[15] = 1.0f; _cubeVetices[16] = 0.0f; _cubeVetices[17] = 0.0f;
				_cubeVetices[21] = 1.0f; _cubeVetices[22] = 0.0f; _cubeVetices[23] = 0.0f;
				_cubeVetices[27] = 1.0f; _cubeVetices[28] = 0.0f; _cubeVetices[29] = 0.0f;
				_cubeVetices[33] = 1.0f; _cubeVetices[34] = 0.0f; _cubeVetices[35] = 0.0f;
				_cubeVetices[39] = 1.0f; _cubeVetices[40] = 0.0f; _cubeVetices[41] = 0.0f;
				_cubeVetices[45] = 1.0f; _cubeVetices[46] = 0.0f; _cubeVetices[47] = 0.0f;
			}
			break;

		case ENTITY_COLOR::GREEN:
			if (_shape == TypeOfShape::Triangle)
			{
				_triangleVertex[3] =  0.0f;  _triangleVertex[4] = 1.0f;  _triangleVertex[5] = 0.0f;
				_triangleVertex[9] =  0.0f; _triangleVertex[10] = 1.0f; _triangleVertex[11] = 0.0f;
				_triangleVertex[15] = 0.0f; _triangleVertex[16] = 1.0f; _triangleVertex[17] = 0.0f;
			}
			else if (_shape == TypeOfShape::Quad)
			{
				_quadVertex[3] =  0.0f;  _quadVertex[4] = 1.0f;  _quadVertex[5] = 0.0f;
				_quadVertex[9] =  0.0f; _quadVertex[10] = 1.0f; _quadVertex[11] = 0.0f;
				_quadVertex[15] = 0.0f; _quadVertex[16] = 1.0f; _quadVertex[17] = 0.0f;
				_quadVertex[21] = 0.0f; _quadVertex[22] = 1.0f; _quadVertex[23] = 0.0f;
			}
			else if (_shape == TypeOfShape::Cube)
			{
				_cubeVetices[3]  = 0.0f;  _cubeVetices[4] = 1.0f;  _cubeVetices[5] = 0.0f;
				_cubeVetices[9]  = 0.0f; _cubeVetices[10] = 1.0f; _cubeVetices[11] = 0.0f;
				_cubeVetices[15] = 0.0f; _cubeVetices[16] = 1.0f; _cubeVetices[17] = 0.0f;
				_cubeVetices[21] = 0.0f; _cubeVetices[22] = 1.0f; _cubeVetices[23] = 0.0f;
				_cubeVetices[27] = 0.0f; _cubeVetices[28] = 1.0f; _cubeVetices[29] = 0.0f;
				_cubeVetices[33] = 0.0f; _cubeVetices[34] = 1.0f; _cubeVetices[35] = 0.0f;
				_cubeVetices[39] = 0.0f; _cubeVetices[40] = 1.0f; _cubeVetices[41] = 0.0f;
				_cubeVetices[45] = 0.0f; _cubeVetices[46] = 1.0f; _cubeVetices[47] = 0.0f;
			}
			break;

		case ENTITY_COLOR::BLUE:
			if (_shape == TypeOfShape::Triangle)
			{
				_triangleVertex[3] =  0.0f;  _triangleVertex[4] = 0.0f;  _triangleVertex[5] = 1.0f;
				_triangleVertex[9] =  0.0f; _triangleVertex[10] = 0.0f; _triangleVertex[11] = 1.0f;
				_triangleVertex[15] = 0.0f; _triangleVertex[16] = 0.0f; _triangleVertex[17] = 1.0f;
			}
			else if (_shape == TypeOfShape::Quad)
			{
				_quadVertex[3] =  0.0f;  _quadVertex[4] = 0.0f;  _quadVertex[5] = 1.0f;
				_quadVertex[9] =  0.0f; _quadVertex[10] = 0.0f; _quadVertex[11] = 1.0f;
				_quadVertex[15] = 0.0f; _quadVertex[16] = 0.0f; _quadVertex[17] = 1.0f;
				_quadVertex[21] = 0.0f; _quadVertex[22] = 0.0f; _quadVertex[23] = 1.0f;
			}
			else if (_shape == TypeOfShape::Cube)
			{
				_cubeVetices[3]  = 0.0f;  _cubeVetices[4] = 0.0f;  _cubeVetices[5] = 1.0f;
				_cubeVetices[9]  = 0.0f; _cubeVetices[10] = 0.0f; _cubeVetices[11] = 1.0f;
				_cubeVetices[15] = 0.0f; _cubeVetices[16] = 0.0f; _cubeVetices[17] = 1.0f;
				_cubeVetices[21] = 0.0f; _cubeVetices[22] = 0.0f; _cubeVetices[23] = 1.0f;
				_cubeVetices[27] = 0.0f; _cubeVetices[28] = 0.0f; _cubeVetices[29] = 1.0f;
				_cubeVetices[33] = 0.0f; _cubeVetices[34] = 0.0f; _cubeVetices[35] = 1.0f;
				_cubeVetices[39] = 0.0f; _cubeVetices[40] = 0.0f; _cubeVetices[41] = 1.0f;
				_cubeVetices[45] = 0.0f; _cubeVetices[46] = 0.0f; _cubeVetices[47] = 1.0f;
			}
			break;
		}
	}

	void Shape::SetColor(float r, float g, float b)
	{
		if (_shape == TypeOfShape::Triangle)
		{
			_triangleVertex[3] = r;  _triangleVertex[4] = g;  _triangleVertex[5] = b;
			_triangleVertex[9] = r; _triangleVertex[10] = g; _triangleVertex[11] = b;
			_triangleVertex[15] = r; _triangleVertex[16] = g; _triangleVertex[17] = b;
		}
		else if (_shape == TypeOfShape::Quad)
		{
			_quadVertex[3] = r;  _quadVertex[4] = g;  _quadVertex[5] = b;
			_quadVertex[9] = r; _quadVertex[10] = g; _quadVertex[11] = b;
			_quadVertex[15] = r; _quadVertex[16] = g; _quadVertex[17] = b;
			_quadVertex[21] = r; _quadVertex[22] = g; _quadVertex[23] = b;
		}
		else if (_shape == TypeOfShape::Cube)
		{
			_cubeVetices[3]  = r;  _cubeVetices[4] = g;  _cubeVetices[5] = b;
			_cubeVetices[9]  = r; _cubeVetices[10] = g; _cubeVetices[11] = b;
			_cubeVetices[15] = r; _cubeVetices[16] = g; _cubeVetices[17] = b;
			_cubeVetices[21] = r; _cubeVetices[22] = g; _cubeVetices[23] = b;
			_cubeVetices[27] = r; _cubeVetices[28] = g; _cubeVetices[29] = b;
			_cubeVetices[33] = r; _cubeVetices[34] = g; _cubeVetices[35] = b;
			_cubeVetices[39] = r; _cubeVetices[40] = g; _cubeVetices[41] = b;
			_cubeVetices[45] = r; _cubeVetices[46] = g; _cubeVetices[47] = b;
		}
	}
	void Shape::TriggerCollision(Entity* other)
	{

	}

}