#include "Traingle.h"

Triangle::Triangle(){
    int side = 8;
    static GLfloat vdata[3] = {
        {0.0, 0.0, 0.0}, {side, 0.0, 0.0}, {side, side, 0.0}
    };
}
