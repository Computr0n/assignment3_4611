#ifndef EARTH_HPP
#define EARTH_HPP

#include "engine.hpp"
#include <vector>
using glm::vec2;
using glm::vec3;

class Earth {
public:
    void initialize(Engine *engine, int slices, int stacks, float spherical);
    float isSpherical();
    void setSpherical(float spherical);
    vec3 getPosition(float latitude, float longitude);
    vec3 getNormal(float latitude, float longitude);
    void draw(bool textured);
protected:
    int slices, stacks;
    int nVertices, nTriangles;
    float spherical;
    Engine *engine;

    // TODO: Define the necessary buffers and texture.
    // Feel free to add helper methods to update the buffers.

};

inline void Earth::initialize(Engine *e, int sl, int st, float sp) {
    engine = e;
    slices = sl;
    stacks = st;
    spherical = sp;

    // TODO: Initialize nVertices, nTriangles, buffers, texture

}

inline float Earth::isSpherical() {
    return spherical;
}

inline void Earth::setSpherical(float s) {
    spherical = s;

    // TODO: Also update the relevant buffers.
    // You should only need to update two buffers, not all of them.

}

inline vec3 Earth::getPosition(float latitude, float longitude) {
    vec3 rectangularPosition(0,0,0), sphericalPosition(0,0,0);

    // TODO compute vertex positions on rectangle and sphere

    if (spherical == 0)
        return rectangularPosition;
    else if (spherical == 1)
        return sphericalPosition;
    else {

        // TODO compute the interpolated position
        return vec3(0,0,0);

    }
}

inline vec3 Earth::getNormal(float latitude, float longitude) {
    vec3 rectangularNormal(0,0,0), sphericalNormal(0,0,0);

    // TODO compute vertex positions on rectangle and sphere

    if (spherical == 0)
        return rectangularNormal;
    else if (spherical == 1)
        return sphericalNormal;
    else {

        // TODO compute the interpolated normal
        return vec3(0,0,0);

    }
}

inline void Earth::draw(bool textured) {

    // TODO: Draw the mesh (with or without texture, depending on the input)

}

#endif
