#ifndef CUBE_H
#define CUBE_H

#include "..\Entity\Entity.h"
//#include "..\Sprite\Sprite.h"
#include "../TextureImporter/TextureImporter.h"

namespace Engine
{

	class EXPORT_API Cube : public Entity
	{
		//Sprite* cube[6];
		//vec3 facesPositions[6] = {
		//	vec3(0.0f, 0.0f, 0.5f),
		//	vec3(0.0f, 0.0f, -0.5f),
		//	vec3(0.5f, 0.0f, 0.0f),
		//	vec3(-0.5f, 0.0f, 0.0f),
		//	vec3(0.0f, 0.5f, 0.0f),
		//	vec3(0.0f, -0.5f, 0.0f)
		//};
		//vec3 facesRotations[6] = {
		//	vec3(0.0f, 0.0f, 0.0f),
		//	vec3(0.0f, 0.0f, 0.0f),
		//	vec3(0.0f, 90.0f, 0.0f),
		//	vec3(0.0f, -90.0f, 0.0f),
		//	vec3(90.0f, 0.0f, 0.0f),
		//	vec3(-90.0f, 0.0f, 0.0f)
		//};
        static const int vertexLength = 192;
        float vertexMaterial[vertexLength] = {
            // positions          // normal                // texture coords
             0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // top left 

             0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

             0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 1.0f
        };
        static const int indexLength = 36;
        unsigned int index[indexLength] = {
            0, 1, 3, // first triangle
            1, 2, 3,  // second triangle
            4, 5, 7,
            5, 6, 7,
            8, 9, 11,
            9, 10, 11,
            12, 13, 15,
            13, 14, 15,
            16, 17, 19,
            17, 18, 19,
            20, 21, 23,
            21, 22, 23
        };
        TextureData _data;
        bool _alpha = false;
        TextureImporter TI;
	public:
        Cube(const char* texture, Renderer* renderer);
        ~Cube();
		void UpdatePosition();
		void Draw();
		void TriggerCollision(Entity* other) override;
	};
}	
#endif // !CUBE_H


