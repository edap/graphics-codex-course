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

This amount of light is just a fraction of the light that has left `Y` in direction `X`. The rays that reaches `X` are a lot, it is not just this segment,

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

This is the core, getting this picture means getting 90% of the renderer.

![The Light Field](img/light-model-3.jpg)

In order, you need to:

- Find the point X that scatters light in direction P. Here you use the ray casting algorithm. Because this point it is not just a point, but it contains other information, light shading normal, geometric noraml, color etc.. we need a better datastructure than a glm::vec3. G3D is using a `Surfel`, in OF there is no such thing, I therefore created the class `Surfel`.
- Once you have the Surfel, you apply the equation that you see in the first picture of the paragraph "The Light Field". Pay attention, you have to *invert the direction of the light!*, `wo` it is simply equal to `-wi`. This part is in the `RayTracer.cpp` file, method `RayCaster::L_i(const Ray& ray)`
- Estimate emitted radiance. This is the radiance that the surface is emitting. In my current implementation it is null, as 90% of the material are usually not emissive
- Find out scattered radiance. A simple approximation of scattered radiance is to calculate just the light that hot `X` directly from point emitters (in my case an instance of `ofLight`). This is called *direct illumination*

### Dynamic range
The problem is that the color range that our monitor is giving us does not corrispond to reality. A black image on monitor in a room it is still glowing, and a white image on a monitor in a park in a sunny day is fairly dim, you can not compete with the power of the sun. `Tone Mapping` is just a way to put the colors of an image in a way that look reasonable. Desaturation, Bloom and Gamma encoding are just tree way that you can use to adjust your image in order to have a range of color that looks more realistic.
I did not implement any of this corrections in my renderer.


## Ray Caster loop

The core of the ray caster is the method to find an intersetion between a ray and a mesh. When the mesh is a sphere, you can use an analytical solution to find it, as the equation that describe a sphere it is easier compared to the equation that you have to use when looking for the intersection with a triangle. But as mesh are made out of triangle, I implemented just a method that find the intersection with a trangle. As GLM already provide one, I've used that one, `glm::intersectRayTriangle`. You can see the implementation in the method `findFirstIntersection` in the `RayCaster` class. In that method implementation there are also comments that explain how to solve some problems, like ordering the intersection when there is more than one intersection between a ray and a triangle.

in pseudo code, a ray casting loop does this:

```
for(each x and y in the virtual image plane){
    ray = findThePrimaryRay(x,y,camera);
    if (intersect(ray, mesh)) {
        // shade the intersection point. What is the emitted/reflected light towards the camera?
        return getShadePointColor();
    } else {
        return backGroundColor;
    }
}
```

*P.S.* note, this pseudocode refers to what is called a `forward shading`, in contrast to `deferred shading` [def. shading](https://en.wikipedia.org/wiki/Deferred_shading). In my renderer, I've implemented a forward shading.

#### Texture coordinates
This part is yet not implemented

## Shading


