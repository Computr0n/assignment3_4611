#ifndef EARTH_HPP
#define EARTH_HPP

#include "engine.hpp"
#include <vector>
using namespace std;
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

    VertexBuffer vertexBuffer, normalBuffer, texCoordBuffer;
    ElementBuffer indexBuffer;
    Texture texture;
};

inline void Earth::initialize(Engine *e, int sl, int st, float sp) {
    engine = e;
    slices = sl;
    stacks = st;
    spherical = sp;

    // TODO: Initialize nVertices, nTriangles, buffers, texture
	nVertices = (slices + 1)*(stacks + 1);
	nTriangles = 2 * slices * stacks;

	vector<vec3> vertices, normals;
	vector<vec2> texCoords;
	for (int x = 0; x <= slices; x++) {
		for (int y = 0; y <= stacks; y++) {
			vertices	.push_back(getPosition(-90 + (180)*x / slices, -180 + (360) * y / stacks));
			normals		.push_back(getNormal(-90 + (180)*x / slices, -180 + (360) * y / stacks));
			texCoords	.push_back(vec2(x / slices, y / stacks));
		}
	}
	
	vertexBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec3));
	engine->copyVertexData(vertexBuffer, &vertices[0], nVertices * sizeof(vec3));
	normalBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec3));
	engine->copyVertexData(normalBuffer, &normals[0], nVertices * sizeof(vec3));
	texCoordBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec2));
	engine->copyVertexData(texCoordBuffer, &texCoords[0], nVertices * sizeof(vec2));
	
	vector<int> indices;
	for (int i = 0; i < slices; i++) {
		indices.push_back(i * 2);
		indices.push_back(i * 2 + 2);
		indices.push_back(i * 2 + 1);
	}

	int nIndices = nTriangles*3;
	indexBuffer = engine->allocateElementBuffer(nIndices * sizeof(int));
	engine->copyElementData(indexBuffer, &indices[0], nIndices * sizeof(int));
	texture = engine->loadTexture(Config::textureFile);
}

inline float Earth::isSpherical() {
    return spherical;
}

inline void Earth::setSpherical(float s) {
    spherical = s;

    // TODO: Also update the relevant buffers.
    // You should only need to update two buffers, not all of them.

}

//Latitude will be from -90 to 90
//Longitude will be between -180 to 180
inline vec3 Earth::getPosition(float latitude, float longitude) {
	if (spherical == 0){
		vec3 rectangularPosition((longitude / 180)* M_PI, (latitude / 90)* (M_PI / 2), 0);
		return rectangularPosition;
	} else if (spherical == 1) {
		vec3 sphericalPosition(0, 0, 0);
		return sphericalPosition;
	} else {

        // TODO compute the interpolated position
        return vec3(0,0,0);

    }
}

inline vec3 Earth::getNormal(float latitude, float longitude) {
    vec3 rectangularNormal(0,0,0), sphericalNormal(0,0,0);

    // TODO compute vertex positions on rectangle and sphere

	if (spherical == 0) {
		rectangularNormal = vec3(0, 0, 1);
		return rectangularNormal;
	} else if (spherical == 1) { 
        return sphericalNormal;
    } else {

        // TODO compute the interpolated normal
        return vec3(0,0,0);

    }
}

inline void Earth::draw(bool textured) {

    // TODO: Draw the mesh (with or without texture, depending on the input)

	// Draw mesh
	engine->setVertexArray(vertexBuffer);
	engine->setNormalArray(normalBuffer);
	engine->setTexCoordArray(texCoordBuffer);

	if (textured)
		engine->setTexture(texture);
	
	engine->drawElements(GL_TRIANGLES, indexBuffer, nTriangles*3);
}

#endif
