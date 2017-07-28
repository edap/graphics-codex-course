#include "RayCaster.h"

RayCaster::RayCaster(ofMesh _mesh){
    mesh = _mesh;
};

// C++ Ray Casting implementation following http://graphicscodex.com

void RayCaster::traceImage(const PinholeCamera& camera, shared_ptr<ofImage>& image) const{
    const int width = int(image->getWidth());
    const int height = int(image->getHeight());

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            glm::vec3 P;
            glm::vec3 w;

            // Find the ray through (x, y) and the center of projection
            camera.getPrimaryRay(float(x) + 0.5f, float(y) + 0.5f, width, height, P, w);
            image->setColor(x, y, L_i(P, w));
        }
    }
    image->update();
}

// Debugging implementation that computes white if there is any surface on this ray and black when there is not.
// This method return the incoming light for X. The radiance need to be calculated properly, for now it is just black and white,
// In the future it will be

/*
Note dal libro: The first one is easy: iterate over the lights and multiply three values: the biradiance from the light, the value of the scattering distribution function, and the cosine of the angle of incidence (a dot product).
*/

ofColor RayCaster::L_i(const glm::vec3& X, const glm::vec3& wi) const{
    // for all the triangles in a mesh
    // Find the first intersection (and the closest!) with the scene
    //const shared_ptr<Surfel>& s = findFirstIntersection(X, wi); TODO

    vector<ofMeshFace> faces = this->mesh.getUniqueFaces();
    bool found = false;
    for(ofMeshFace face : faces){
        float t;
        float baricenter[3];
        glm::vec3 v[3];
        v[0] = face.getVertex(0);
        v[1] = face.getVertex(1);
        v[2] = face.getVertex(2);

        found = rayTriangleIntersect(X, wi, v, baricenter, t);
        if(found) {
            break;
        }
    }
    //if (notNull(s)) {
    //return ofColor(255,0,255);
    //} else {
    //return ofColor(0,0,0);
    //}

    if (found) {
       return ofColor(255,0,255);
    } else {
       return ofColor(0,0,0);
    }
}

/* It find the intersection between a ray (with origin P and direction w) and the scene.
 If ray P + tw hits triangle V[0], V[1], V[2], then the function returns true, stores the barycentric coordinates in b[],
 and stores the distance to the intersection in t. Otherwise returns false and the other output parameters are undefined.*/
bool RayCaster::rayTriangleIntersect(const glm::vec3& P, const glm::vec3& w, const glm::vec3 V[3], float b[3], float& t) const{
    // Edge vectors
    double eps = 0.1; //TODO, test this value
    const glm::vec3& e_1 = V[1] - V[0];
    const glm::vec3& e_2 = V[2] - V[0];

    // Face normal
    const glm::vec3& n = glm::normalize(glm::cross(e_1, e_2));

    const glm::vec3& q = glm::cross(w, e_2);
    const float a = glm::dot(e_1, q);

    // Backfacing / nearly parallel, or close to the limit of precision?
    if ((glm::dot(n, w) >= 0) || (abs(a) <= eps)) return false;

    const glm::vec3& s = (P - V[0]) / a;
    const glm::vec3& r = glm::cross(s, e_1);

    b[0] = glm::dot(s, q);
    b[1] = glm::dot(r, w);
    b[2] = 1.0f - b[0] - b[1];

    // Intersected outside triangle?
    if ((b[0] < 0.0f) || (b[1] < 0.0f) || (b[2] < 0.0f)) return false;

    t = glm::dot(e_2, r);
    return (t >= 0.0f);
}
