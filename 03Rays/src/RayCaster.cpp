#include "RayCaster.h"

RayCaster::RayCaster(const vector<of3dPrimitive>& _primitives, const vector<ofLight>& _lights){
    primitives = _primitives;
    lights = _lights;
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


    const shared_ptr<Surfel>& surfelY = findFirstIntersectionWithThePrimitives(ray);
    if (surfelY) {
        return L_0(surfelY, -ray.direction);
    } else {
        return ofColor(0,0,0);
    }



//    for(of3dPrimitive primitive : primitives){
//        const shared_ptr<Surfel>& surfelY = findFirstIntersection(ray, primitive.getMesh(), primitive.getGlobalTransformMatrix());
//
//        //if (notNull(s)) TODO, if a ray is found, create a Surfel
//        if (surfelY) {
//            return L_0(surfelY, -ray.direction);
//        } else {
//            return ofColor(0,0,0);
//        }
//    }
}

// This method find the first intersection between a ray and a mesh.
// If an intersection is founded, it returns a surfel, otherwise null.
shared_ptr<Surfel> RayCaster::findFirstIntersectionWithThePrimitives(const Ray& ray) const{
    // at the beginning, no intersection is found and the distance to the closest surface
    // is set to an high value;
    bool found = false;
    float distanceToTheClosestSurface = numeric_limits<float>::max();
    glm::vec3 faceNormal;
    glm::vec3 position;
    glm::vec3 rayDirection;
    ofFloatColor color;
    // then we iterate through all the triangles in all the meshes, searching
    // for the closest intersection
    for (const of3dPrimitive& primitive : this->primitives) {
        for (const ofMeshFace& face : primitive.getMesh().getUniqueFaces()) {
            glm::vec3 baricenter;
            bool intersection = glm::intersectRayTriangle(
                                    ray.origin, ray.direction,
                                    glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(0), 1.f)),
                                    glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(1), 1.f)),
                                    glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(2), 1.f)),
                                    baricenter);
            // when an intersection is found, it updates the distanceToTheClosestSurface value
            // this value is used to order the new intersections, if a new intersection with a smaller baricenter.z
            // value is found, this one will become the new intersection
            if (intersection) {
                if (baricenter.z < distanceToTheClosestSurface) {
                    found = true;
                    if(face.hasColors()) {
                        color = face.getColor(1);
                    } else {
                        color = ofFloatColor(1.f,1.f,1.f);
                    };
                    distanceToTheClosestSurface = baricenter.z;
                    faceNormal = face.getFaceNormal();
                    position = getPointOnTriangle(ray, baricenter);
                    rayDirection = ray.direction;
                }
            }
        }
    }

    if (found) {
        return shared_ptr<Surfel>(new Surfel(faceNormal, rayDirection, position, color));
    } else {
        return nullptr;
    }
};

// It computes the light leaving Y, which is the same as
// the light entering X when the medium is non-absorptive
ofColor RayCaster::L_0(const shared_ptr<Surfel>& surfelY, const glm::vec3 wo) const{
    // as emitted Radiance is 0, for now, I will just caclulate the direct scattered radiance
    //return surfelX->emittedRadiance(wo) + L_scatteredDirect(surfelX, wo);
    return L_scatteredDirect(surfelY, wo);
}

/*
 From the chapter "Direct Illumination":
 Note that actual parameter surfelY is now called surfelX in method L_scatteredDirect.
 I changed the frame of reference by advancing one step closer to the light along a
 transport path. As in all equations so far, X is the point at which radiance is being
 scattered and Y is the next node closer to the light on the light transport path.
*/
ofFloatColor RayCaster::L_scatteredDirect(const shared_ptr<Surfel>& surfelX,const glm::vec3 wo) const{
    glm::vec3 Light = surfelX->emittedRadiance(wo);
    for (int i = 0; i<lights.size(); i++) {
        glm::vec3 lightPos = lights[i].getGlobalPosition();
        glm::vec3 offset = lightPos - surfelX->getPosition();
        const float distanceToLight = glm::length(offset);
        glm::vec3 wi = glm::normalize(offset);

        if (visible(surfelX->getPosition(), wi, distanceToLight)) {

            glm::vec3 color = surfelX->getColor();
            // light power is not implemented in ofLight,
            // I use a getDiffuseColor().getBrightness() for this
            float lightPower = lights[i].getDiffuseColor().getBrightness() * 10;
            float biradiance = lightPower / (4 * PI * sqrt(distanceToLight));

            //lambertian light
            float dProd = abs(glm::dot(wi, surfelX->getGeometricNormal()));
            glm::vec3 finiteScatteringDensity = surfelX->finiteScatteringDensity(wi, wo);
            Light +=
                biradiance * // comment out this when debugging
                finiteScatteringDensity *
                glm::vec3( dProd ) *
                color;
        }
    }
    return ofFloatColor(Light.x, Light.y, Light.z);
};

bool RayCaster::visible(const glm::vec3& P, const glm::vec3& direction, const float& distance) const{
    const Ray ray = Ray(P + direction * CONST_EPSILON, direction);
    float dist = distance - CONST_EPSILON;

    for (const of3dPrimitive& primitive : this->primitives) {
        for (const ofMeshFace& face : primitive.getMesh().getUniqueFaces()) {
            glm::vec3 baricenter;
            // Test each potential shadow caster to see if it lies between P and the light
            bool intersection = glm::intersectRayTriangle(
                                                          ray.origin, ray.direction,
                                                          glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(0), 1.f)),
                                                          glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(1), 1.f)),
                                                          glm::vec3(primitive.getGlobalTransformMatrix() * glm::vec4(face.getVertex(2), 1.f)),
                                                          baricenter);
            if (intersection) {
                if (baricenter.z < dist) {
                    // Ah! This triangle is closer than the light. Shadow
                    return false;
                }
            }
        }
    }
    return true;
}


/*
 This method takes as argument a ray and the baricentric coordinates and returns
 the exact point on the triangle where the intersection happened.
 The variable values that are stored in the baryPosition vector need to be
 explained, because there is no documentation in the glm website for the
 glm::intersectRayTriangle method, but just in this github issue 
 https://github.com/g-truc/glm/issues/6

 the baryPosition output uses barycentric coordinates for the x and y components.
 The z component is the scalar factor for ray.

 That is,
 1.0 - baryPosition.x - baryPosition.y = actual z barycentric coordinate

 if you compute the point inside the triangle that corresponds to those barycentric coordinates, you'll find the exact same answer as if you did:
 origin + direction * baryPosition.z
*/

glm::vec3 RayCaster::getPointOnTriangle(const Ray& _ray, const glm::vec3& _baryPosition) const {
    return _ray.origin + (_ray.direction * _baryPosition.z);
};

