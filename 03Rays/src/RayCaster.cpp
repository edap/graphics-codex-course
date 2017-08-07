#include "RayCaster.h"

RayCaster::RayCaster(const ofMesh& _mesh, glm::mat4 _globalTransfMatrix){
    mesh = _mesh;
    globalTransfMatrix = _globalTransfMatrix;
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
            image->setColor(x, y, L_i(Ray(P, w)));
        }
    }
    image->update();
}

// Debugging implementation that computes white if there is any surface on this ray and black when there is not.
// This method return the incoming light for X. The radiance need to be calculated properly, for now it is just black and white,
// In the future it will be
/*
from the book: The first one is easy: iterate over the lights and multiply three values: the biradiance from the light, the value of the scattering distribution function, and the cosine of the angle of incidence (a dot product).
*/

ofColor RayCaster::L_i(const Ray& ray) const{
    // for all the triangles in a mesh
    // Find the first intersection (and the closest!) with the scene

    const shared_ptr<Surfel>& found = findFirstIntersection(ray, this->mesh);

    //if (notNull(s)) TODO, if a ray is found, create a Surfel
    if (found) {
       return ofColor(255,255,255);
    } else {
       return ofColor(0,0,0);
    }
}

// Sei al punto b del paragrafo "Measure Incident Light at each Pixel." in "A model of Light"
shared_ptr<Surfel> RayCaster::findFirstIntersection(const Ray& ray, const ofMesh& mesh) const{
    vector<ofMeshFace> faces = mesh.getUniqueFaces();
    bool found = false;
    for (ofMeshFace face : faces) {
        glm::vec3 baricenter;
        found = glm::intersectRayTriangle(
                                          ray.origin, ray.direction,
                                          glm::vec3(globalTransfMatrix * glm::vec4(face.getVertex(0), 1.f)),
                                          glm::vec3(globalTransfMatrix * glm::vec4(face.getVertex(1), 1.f)),
                                          glm::vec3(globalTransfMatrix * glm::vec4(face.getVertex(2), 1.f)),
                                          baricenter);
        if (found) {
            glm::vec3 faceNormal = face.getFaceNormal();
            return shared_ptr<Surfel>(new Surfel());
            break;
        }
    }
    return nullptr;
};


/* It find the intersection between a ray (with origin P and direction w) and the scene.
 If ray P + tw hits triangle V[0], V[1], V[2], then the function returns true, stores the barycentric coordinates in b[],
 and stores the distance to the intersection in t. Otherwise returns false and the other output parameters are undefined.*/
bool RayCaster::rayTriangleIntersect(const glm::vec3& P, const glm::vec3& w, const vector<glm::vec3> V, float b[3], float& t) const{
    // Edge vectors
    double eps = 0.01; //TODO, test this value
    const glm::vec3& e_1 = V[1] - V[0];
    const glm::vec3& e_2 = V[2] - V[0];

    // Face normal
    const glm::vec3& n = glm::normalize(glm::cross(e_1, e_2));

    const glm::vec3& q = glm::cross(w, e_2);
    const float a = glm::dot(e_1, q);
    //cout << a << endl;
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
