#pragma once
#include "ofMain.h"

class Surfel {
    public:
    Surfel();
    const float emittedRadiance(glm::vec3 wo);
    glm::vec3 shadingNormal;
    glm::vec3 position;
    //float light;
};
