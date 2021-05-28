#include "Skydome.h"
#include <math.h>
#include <vector>
#define PI 3.14159265359

namespace GE {
	Skydome::Skydome()
	{
	}

	Skydome::~Skydome()
	{
	}

	void Skydome::Init(int _radius, int _resolution)
	{
		//Create temporary placeholder for verts
		std::vector<Vertex> tempVerticies;

		//Define the step with the resolution
		float azimuthStep = (2.0f * PI) / (float)(_resolution - 1);
		float elevationStep = PI / (float)(_resolution - 1);

		float x, y, z, u, v, nx, ny, nz;
		float theta, phi;

		for (int latitude = 0; latitude < _resolution + 1; latitude++) {
			for (int longitude = 0; longitude < _resolution + 1; longitude++) {
				//Calc the elevation and azimuth angle
				theta = PI / 2.0f - longitude * elevationStep;
				phi = latitude * azimuthStep;
				//vertex position
				x = (_radius * cosf(theta)) * cosf(phi);
				z = (_radius * cosf(theta)) * sinf(phi);
				y = _radius * sinf(theta);
				//Calc UV coords
				u = (float)latitude / (float)_resolution;
				v = (float)longitude / (float)_resolution;
				//Calc normals
				nx = -x;
				ny = -y;
				nz = -z;
				float mag = sqrt((nx * nx) + (ny * ny) + (nz * nz));
				float fac = 1 / mag;
				nx *= fac;
				ny *= fac; 
				nz *= fac;
				tempVerticies.emplace_back(Vertex(x, y, z, u, v, nx, ny, nz));
			}
		}

		std::vector<unsigned int> indicies;
		//Calculate indecies
		unsigned int c, n;
		for (int latitude = 0; latitude < _resolution - 1; latitude++) {
			c = latitude * (_resolution + 1);
			n = c + _resolution + 1;
			for (int longitude = 0; longitude < _resolution - 1; longitude++) {
				if (longitude != 0) {
					//There is no leftmost triangle
					indicies.push_back(c);
					indicies.push_back(n);
					indicies.push_back(c + 1);
				}
				if (longitude != _resolution - 1) {
					//No rightmost trianlge
					indicies.push_back(c + 1);
					indicies.push_back(n);
					indicies.push_back(n + 1);
				}
				c++; //<< Possible coding pun?
				n++;
			}
		}

		numVerticies = indicies.size();
		verticies = new Vertex[numVerticies];

		for (int i = 0; i < indicies.size(); i++) {
			verticies[i] = tempVerticies[indicies[i]];
		}
	}
}
