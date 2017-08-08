#include "Surfel.h"

Surfel::Surfel(const glm::vec3& _faceNormal, const glm::vec3& _rayDirection, const glm::vec3 _position){
    geometricNormal = _faceNormal;
    position = _position;
//  We'll allow all of our triangles to be Òtwo sidedÓ for now, so that we see consistent results from the front and back of the triangle. When you detect a hit on the triangle, if the dot product of the ray direction and the counter-clockwise normal is positive, then the ray actually struck the triangle from behind.
    if(glm::dot(_faceNormal, _rayDirection) >= 0){
        backface = true;
    }

}

float Surfel::emittedRadiance(glm::vec3 wo) const {
    return 0;
};

glm::vec3 Surfel::getColor() const{
    return glm::vec3(1.0,1.0,1.0);
}
