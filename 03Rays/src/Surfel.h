#pragma once
#include "ofMain.h"

class Surfel {
    public:
    Surfel(glm::vec3 _faceNormal);
    float emittedRadiance(glm::vec3 wo) const;
    glm::vec3 shadingNormal;
    glm::vec3 position;
    //float light;
};
