#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "..\Export\Export.h"
#include "..\Entity\Entity.h"
#include "..\Renderer\Renderer.h"

namespace Engine
{
	class EXPORT_API Shape : public Entity
	{
	private:
		float _triangleVertex[18] = {
			/*Pos*/ -0.1f,  0.0f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/  0.0f,  0.2f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/  0.1f,  0.0f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f
		};

		float _quadVertex[24] = {
			/*Pos*/-0.1f,  0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/-0.1f, -0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/ 0.1f, -0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/ 0.1f,  0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f
		};
		float _cubeVetices[48] = {
			// posición X, Y, Z
			-0.5f, -0.5f, -0.5f, /* 0 Color*/ 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, /* 1 Color*/ 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, /* 2 Color*/ 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, /* 3 Color*/ 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, /* 4 Color*/ 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, /* 5 Color*/ 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, /* 6 Color*/ 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, /* 7 Color*/ 1.0f, 0.0f, 0.0f
		};

		unsigned int _indexTris[3] = {
			0,1,2,
		};

		unsigned int _indexPos[6] = {
			0,1,2,
			3,2,0
		};
		unsigned int _cubeIndices[36] = {
			// Cara de atrás
			0, 1, 2,
			2, 3, 0,
			// Cara de adelante
			4, 5, 6,
			6, 7, 4,
			// Izquierda
			0, 4, 7,
			7, 3, 0,
			// Derecha
			1, 5, 6,
			6, 2, 1,
			// Abajo
			0, 1, 5,
			5, 4, 0,
			// Arriba
			3, 2, 6,
			6, 7, 3
		};

		int _vertexSize;
		float* _vertex;

		unsigned int _vao; // Vertex Array Obj
		unsigned int _vbo; // Vertex Buffer Obj
		unsigned int _ebo; // Index Buffer Obj
		
		TypeOfShape _shape;
		unsigned int _modelUniform;
		Renderer* _renderer;

	public:
		Shape(Renderer* renderer);
		~Shape();
		void InitShape(TypeOfShape type);
		void Draw();

		void SetColor(ENTITY_COLOR color) override;
		void SetColor(float r, float g, float b) override;
		void TriggerCollision(Entity* other);

	};
}

#endif

