#pragma once
#include "ofMain.h"

class Surfel {
    public:
    Surfel();
    float emittedRadiance(glm::vec3 wo) const;
    glm::vec3 shadingNormal;
    glm::vec3 position;
    //float light;
};
