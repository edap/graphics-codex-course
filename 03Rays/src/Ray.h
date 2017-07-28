#pragma once
#include "ofMain.h"

class Ray {
public:
    /* Starting point $P$ */
    glm::vec3   origin;
    /* Unit vector $\w$ */
    glm::vec3  direction;
};
