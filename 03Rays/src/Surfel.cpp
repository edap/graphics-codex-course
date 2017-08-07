#include "Surfel.h"

Surfel::Surfel(glm::vec3 _faceNormal){
    shadingNormal = _faceNormal;
}

float Surfel::emittedRadiance(glm::vec3 wo) const {
    return 0;
};
