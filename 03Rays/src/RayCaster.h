#pragma once
#include "ofMain.h"
#include "Surfel.h"
#include "PinholeCamera.h"

// It takes a primary ray, it intersect it with a scene and it return a pointer to a surface element.
// A surface element (“surfel”) [Pfister2000Surfels] contains the intersection position, normal, and material information
// that will be useful for shading.
// If there is no intersection, then the pointer returned will be NULL. A NULL shared_ptr casts to the boolean false value.

class RayCaster {
public:
    RayCaster();
    //iterates overall pixels calling traceRay
    void traceImage(const PinholeCamera& camera, shared_ptr<ofImage>& image) const;
    // 
    ofColor L_i(const glm::vec3& X, const glm::vec3& wi) const;
    // Find the first intersection with the scene
    bool rayTriangleIntersect(const glm::vec3& P, const glm::vec3& w, const glm::vec3 V[3], float b[3], float& t);
    //const shared_ptr<Surfel> findFirstIntersection(glm::vec3 X, glm::vec3 wi);


};
