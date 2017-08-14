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

![The Light Field](img/light-field.jpg)

This formula denotes the Light ad P propagating in direction w

In an "empty space", where there aren't mediums that are absorbing light, the light must be conserved along a ray. This means that in an empty space and with nothing between X and Y, like in the sketch, the light that leaves X in direction P will actually reach P, without any dispersions. This means that what matters, in rendering, are only the events where light change direction.

This skecth focuses only on the segment X -> P.
![The Light Field](img/light-model.jpg)

It is just saying that:
The incoming light `Li` that reaches `P` in direction `wi`, IS EQUAL to the the outcoming light `Lo`, that from the point `X`  goes to `P` in direction `wo`.

This amount of light is just a fraction of the light that has left `Y` in direction `X`. The rays that reaches `X` are a lot, as you see in this picture.

![The Light Field](img/light-model-3.jpg)

That's why the previous equation needs to be improved. See this picture for the second part of the equation
![The Light Field](img/light-model-2.jpg)

*P.S.* a common error is mixing up the direction of the ray. Have a look at the last note in picture number 2.


## A camera model

![A camera model](img/camera-model.jpg)

The implementation of the camera model is in the file `PinholeCamera`. This class has a `position`, a `z_near` distance (llok at the picture to see what it is) and an angle that defines the vertical field of view. The main method that this class has is 'getPrimaryRay'. Given x and y of the image, it find the primary ray.

### A Modern Computational Renderer

#### Load a scene
I've tested the renderer first with a cube, then with a teapot and finally with the Cornell's Box.
I've load an obj file using the ofxAssimpModelLoader addon. This model contains meshes, I've iterated through them and I've converted them to `of3DPrimitive`. See this answer [thread in the OF forum](https://forum.openframeworks.cc/t/get-global-vertices-position-of-an-instance-of-ofxassimpmodelloader/27433/5?u=edapx). This was the easiest way to have the mesh and the global transformation matrix, I need this matrix because the calculation in the ray caster are in word perspective.
It is good practice to separe the data from the ray caster implementation.

#### Measure incident light per pixel



## Ray Caster loop

## Shading


