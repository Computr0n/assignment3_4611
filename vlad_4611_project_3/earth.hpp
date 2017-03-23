#ifndef EARTH_HPP
#define EARTH_HPP

#include "engine.hpp"
#include <vector>
#include "glm/ext.hpp"
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
	void updateBuffers();
protected:
    int slices, stacks;
    int nVertices, nTriangles;
    float spherical;
    Engine *engine;

    // TODO: Define the necessary buffers and texture.
    // Feel free to add helper methods to update the buffers.

	VertexBuffer vertexBuffer, normalBuffer, texCoordBuffer;
	VertexBuffer vertexUpdateBuffer, normalUpdateBuffer;
	ElementBuffer indexBuffer;
    Texture texture;
};

inline void Earth::initialize(Engine *e, int sl, int st, float sp) {
    engine = e;
    slices = sl;
    stacks = st;
    spherical = sp;

	//create buffers for storing new positions for when it comes time to update the position or the normals
	vertexUpdateBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec3));
	normalUpdateBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec3));


	nVertices = (slices + 1)*(stacks + 1);
	nTriangles = 2 * slices * stacks; // 2 triangles for every square. Slice*Stacks squares.

	vector<vec3> vertices, normals;
	vector<vec2> texCoords;
	for (int x = 0; x <= slices; x++) {
		for (int y = 0; y <= stacks; y++) {
			vertices	.push_back(getPosition(-90 + (180)*y / stacks, -180 + (360) * x / slices));
			normals		.push_back(getNormal(-90 + (180)*y / stacks, -180 + (360) * x / slices));

			float xcoord = (x / (float)slices);
			float ycoord = (y / (float)stacks);
			vec2 coords = vec2(xcoord, -ycoord);
			texCoords.push_back(coords);
		}
	}
	
	vertexBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec3));
	engine->copyVertexData(vertexBuffer, &vertices[0], nVertices * sizeof(vec3));
	normalBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec3));
	engine->copyVertexData(normalBuffer, &normals[0], nVertices * sizeof(vec3));
	texCoordBuffer = engine->allocateVertexBuffer(nVertices * sizeof(vec2));
	engine->copyVertexData(texCoordBuffer, &texCoords[0], nVertices * sizeof(vec2));
	
	vector<int> indices;
	for (int x = 0; x < slices; x++) {
		for (int y = 0; y < stacks; y++) {

			indices.push_back((x*(stacks + 1)) + y);
			indices.push_back((x*(stacks + 1)) + y + (stacks + 1) + 1);
			indices.push_back((x*(stacks + 1)) + y + 1);

			indices.push_back((x*(stacks + 1)) + y);
			indices.push_back((x*(stacks + 1)) + y + (stacks + 1));
			indices.push_back((x*(stacks + 1)) + y + (stacks + 1) + 1);
		}
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

//Y = Latitude will be from -90 to 90
//X = Longitude will be between -180 to 180
inline vec3 Earth::getPosition(float latitude, float longitude) {
	vec3 rectangularPosition((longitude / 180)* M_PI, (latitude / 90)* (M_PI / 2), 0);
	vec3 sphericalPosition(cos(glm::radians(latitude))*sin(glm::radians(longitude)), sin(glm::radians(latitude)), cos(glm::radians(latitude))*cos(glm::radians(longitude)));
	if (spherical == 0){
		return rectangularPosition;
	} else if (spherical == 1) {
		return sphericalPosition;
	} else {
		return glm::lerp(rectangularPosition, sphericalPosition, spherical);;
    }
}

inline vec3 Earth::getNormal(float latitude, float longitude) {
    vec3 rectangularNormal(0,0,1), sphericalNormal(0,0,0);

	sphericalNormal = (getPosition(latitude, longitude) - vec3(0, 0, 0));

    // TODO compute vertex positions on rectangle and sphere

	if (spherical == 0) {
		rectangularNormal = vec3(0, 0, 1);
		return rectangularNormal;
	} else if (spherical == 1) { 
        return sphericalNormal;
    } else {

        // TODO compute the interpolated normal
		return glm::lerp(rectangularNormal, sphericalNormal, spherical);;

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
	
	if (textured)
		engine->unsetTexture();
}

inline void Earth::updateBuffers()
{
	vector<vec3> vertices, normals;
	for (int x = 0; x <= slices; x++) {
		for (int y = 0; y <= stacks; y++) {
			vertices.push_back(getPosition(-90 + (180)*y / stacks, -180 + (360) * x / slices));
			normals.push_back(getNormal(-90 + (180)*y / stacks, -180 + (360) * x / slices));

			float xcoord = (x / (float)slices);
			float ycoord = (y / (float)stacks);
			vec2 coords = vec2(xcoord, -ycoord);
		}
	}

	engine->copyVertexData(vertexBuffer, &vertices[0], nVertices * sizeof(vec3));
	engine->copyVertexData(normalBuffer, &normals[0], nVertices * sizeof(vec3));\
}

#endif
