# Ray Caster

-this notes are just for personal use-


This project is an excercise part of the programming projects course [graphix codex](http://graphicscodex.com/) by Morgan McGuire. All the quotes that you see in this files comes from this online book.



## A model of light
It defines a way to summarize Light. Every representaion of the light field is always a simplification.

### Image as digital measurement

> “A real digital camera is a measurement device. It measures the amount of light striking each pixel of its sensor and records it as a number”

Ray caster is simply measuring the light striking each pixel.





### Rays of Lights
Light propagates along a ray through a medium, you can only see the light rays that enter your eyes. If you consider your eye as a surface, you are seeing just the end point of this rays and they look like points. The collection of this point gives you an image.

A mathematical ray has a point and a direction.
As datastructure, I've presented it like this:

```cpp
#pragma once
#include "ofMain.h"

class Ray {
public:
    Ray(glm::vec3 origin, glm::vec3 direction);
    /* Starting point $P$ */
    glm::vec3   origin;
    /* Unit vector $\w$ */
    glm::vec3  direction;
};
```

A *line segment* has a starting point end an ending point.

The light travel along a *line segment*. When I'm doing the calculation, I do not know where this line segment will end, I just know the origin and the direction stored in the ray.

A *light transport path* is a collection of light segments.
The transport paths that I consider in my renderer originate at a surface that generate photons. In the implementaion, this source is an `ofLight` instance

### The Light Field

![The Light Field](img/light-model.jpg)


## A camera model

![A camera model](img/camera-model.jpg)

### A Modern Computational Renderer

#### Load a scene
I've tested the renderer first with a cube, then with a teapot and finally with the Cornell's Box.
I've load an obj file using the ofxAssimpModelLoader addon. This model contains meshes, I've iterated through them and I've converted them to `of3DPrimitive`. See this answer [thread in the OF forum](https://forum.openframeworks.cc/t/get-global-vertices-position-of-an-instance-of-ofxassimpmodelloader/27433/5?u=edapx). This was the easiest way to have the mesh and the global transformation matrix, I need this matrix because the calculation in the ray caster are in word perspective.
It is good practice to separe the data from the ray caster implementation.


## Ray Caster loop

## Shading


