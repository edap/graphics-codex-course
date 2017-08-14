#pragma once
#include "ofMain.h"

//All the position that this class knows has to be global positions

class Surfel {
public:
    Surfel(const glm::vec3& _faceNormal, const glm::vec3& _rayDirection, const glm::vec3 position);
    virtual ~Surfel() {};
    glm::vec3 getPosition() const { return position; };
    glm::vec3 getGeometricNormal() const { return geometricNormal; };
    glm::vec3 getColor() const;
    ofColor finiteScatteringDensity(const glm::vec3& w_i, const glm::vec3& w_o);
    glm::vec3 emittedRadiance(glm::vec3 wo) const;

private:
    glm::vec3 geometricNormal;
    glm::vec3 position;
    //float light;

    //The normal to the patch for shading purposes, i.e., after normal mapping.
    //e.g., the interpolated vertex normal or normal-mapped normal.
    //Always a unit vector.
    glm::vec3 shadingNormal; // this needs to be calculated

    bool backface = false;

};
