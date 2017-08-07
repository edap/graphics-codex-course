#include "Surfel.h"

Surfel::Surfel(const glm::vec3& _faceNormal, const glm::vec3 _position){
    geometricNormal = _faceNormal;
    position = _position;
}

float Surfel::emittedRadiance(glm::vec3 wo) const {
    return 0;
};
