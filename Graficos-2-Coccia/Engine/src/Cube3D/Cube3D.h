#ifndef CUBE3D_H
#define CUBE3D_H
#include "..\Export\Export.h"
#include "..\Renderer\Renderer.h"
#include "..\Entity\Entity.h"

namespace Engine
{
	class EXPORT_API Cube3D : public Entity
	{
        static const int _verticesSize = 24;
        float _vertices[_verticesSize] = {
            // posición X, Y, Z
            -0.5f, -0.5f, -0.5f, // 0
             0.5f, -0.5f, -0.5f, // 1
             0.5f,  0.5f, -0.5f, // 2
            -0.5f,  0.5f, -0.5f, // 3
            -0.5f, -0.5f,  0.5f, // 4
             0.5f, -0.5f,  0.5f, // 5
             0.5f,  0.5f,  0.5f, // 6
            -0.5f,  0.5f,  0.5f  // 7
        };
        static const int _indicesSize = 36;
        unsigned int _indices[_indicesSize] = {
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
        Renderer* _renderer;
        unsigned int _modelUniform;
        unsigned int _vao; // Vertex Array Obj
        unsigned int _vbo; // Vertex Buffer Obj
        unsigned int _ebo; // Index Buffer Obj

    public:
        Cube3D(Renderer* renderer);
        ~Cube3D();
        void Draw();

        void SetColor(ENTITY_COLOR color);
        void SetColor(float r, float g, float b);
        void TriggerCollision(Entity* other);
	};

}
#endif // !CUBE3D_H