#include "Surfel.h"

Surfel::Surfel(const glm::vec3& _faceNormal, const glm::vec3& _rayDirection, const glm::vec3 _position){
    geometricNormal = _faceNormal;
    shadingNormal = _faceNormal; // TODO, this should be calculated, for example from a bump map
    position = _position;
//  We'll allow all of our triangles to be Òtwo sidedÓ for now, so that we see consistent results from the front and back of the triangle. When you detect a hit on the triangle, if the dot product of the ray direction and the counter-clockwise normal is positive, then the ray actually struck the triangle from behind.
    if(glm::dot(_faceNormal, _rayDirection) >= 0){
        backface = true;
    }

}

glm::vec3 Surfel::emittedRadiance(glm::vec3 wo) const {
    return glm::vec3(0.f,0.f,0.f);
};

ofColor finiteScatteringDensity(const glm::vec3& w_i, const glm::vec3& w_o){
    // Surface normal
//    const glm::vec3& n = shadingNormal;
//    if (glm::dot(w_i, n) <= 0.0) {
//        // Transmission is specular-only, so never appears
//        // in finiteScatteringDensity for this BSDF.
//        return ofColor(0.0, 0.0, 0.0);
//    }
}

glm::vec3 Surfel::getColor() const{
    return glm::vec3(1.0,1.0,1.0);
}
