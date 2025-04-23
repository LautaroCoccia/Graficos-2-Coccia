#ifndef FPCamera_H
#define FPCamera_H

#include "Camera.h"

namespace Engine
{
    class EXPORT_API FPCamera : public Camera
    {
    public:
        FPCamera();
        void CameraInput(float deltatime);
    };

}
#endif
