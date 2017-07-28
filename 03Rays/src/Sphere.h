#pragma once
#include "ofMain.h"

class Sphere {
public:
    Sphere(glm::vec3 _c, double _r){ center = _c; radius = _r;}
    glm::vec3 center;
    double radius;

    bool interesect(glm::vec3& P, glm::vec3& w, double &t){
        glm::vec3 p_center = P - center;
        double b = 2 * glm::dot(p_center, w);
    }

};
