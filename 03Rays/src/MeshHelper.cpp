//
//  MeshHelper.cpp
//  03Rays
//
//  Created by DavidePrati on 12/08/17.
//
//

#include "MeshHelper.h"

of3dPrimitive MeshHelper::toPrimitive(const ofMesh& mesh) {
    of3dPrimitive primitive;
    primitive.getMesh().clear();
    primitive.getMesh().append(mesh);
    primitive.getMesh().enableNormals();
    return primitive;
}
