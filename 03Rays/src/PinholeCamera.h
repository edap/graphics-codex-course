#pragma once
#include "ofMain.h"

class PinholeCamera {
public:
    PinholeCamera();
    void draw();
    glm::vec3 centerOfProjection;
    void getPrimaryRay(float x, float y, int width, int height, glm::vec3& P, glm::vec3& w) const;

protected:
    float verticalFieldOfView; //angle y0
    float z_near;
};
