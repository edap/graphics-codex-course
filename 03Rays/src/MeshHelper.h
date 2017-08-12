#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"



class MeshHelper{
public:
    //get an of3dPrimitive from a mesh
    static of3dPrimitive toPrimitive(const ofMesh& mesh);
    // it fullfills a vector of3dPrimitive from an ofxAssimpModelLoader
    //
    static of3dPrimitive readModelAndGetPrimitives(const ofxAssimpModelLoader& model,
                                                vector<of3dPrimitive>& primitives,
                                                ofNode& parentNode);
};
