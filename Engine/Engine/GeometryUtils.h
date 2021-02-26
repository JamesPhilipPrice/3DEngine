#pragma once
#include <cstddef>
#include <GL/glew.h>
#include <vector>

namespace GE {
	struct Vertex {
		//Vertex location
		float x, y, z;
		//Vertex colour
		float u, v;

		Vertex(float _x, float _y, float _z, float _u, float _v) {
			x = _x;
			y = _y;
			z = _z;

			u = _u;
			v = _v;
		}

		Vertex() {
			x = y = z = 0.0f;
			u = v = 0.0f;
		}
	};

	/*unsigned int CreateVBO(const std::vector<Vertex>& verts) {
		unsigned int newBuffer;
		glCreateBuffers(1, &newBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newBuffer);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), (void*)&verts[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
		return newBuffer;
	}

	unsigned int CreateIBO(const std::vector<unsigned int>& indecies) {
		unsigned int newBuffer;
		glGenBuffers(1, &newBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(unsigned int), (void*)&indecies[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
		return newBuffer;
	}*/
}
