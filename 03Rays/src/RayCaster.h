#pragma once
#include "ofMain.h"
#include "Surfel.h"

// It takes a primary ray, it intersect it with a scene and it return a pointer to a surface element.
// A surface element (“surfel”) [Pfister2000Surfels] contains the intersection position, normal, and material information
// that will be useful for shading.
// If there is no intersection, then the pointer returned will be NULL. A NULL shared_ptr casts to the boolean false value.

class RayCaster {
public:
    // Find the first intersection with the scene
    const shared_ptr<Surfel> findFirstIntersection(glm::vec3 X, glm::vec3 wi);

private:
    const glm::vec3 getTraingleIntersection(glm::vec3 ray, float x, float y, float z);
};
