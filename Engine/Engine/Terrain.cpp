#include "Terrain.h"

GE::Terrain::Terrain(std::string _filename, Texture* _texture, float _scale, float _hScale)
{
	scale = _scale;
	hScale = _hScale;
	texture = _texture;

	int width, height, channels;
	SDL_Surface* heightMap = IMG_Load(_filename.c_str());

	width = heightMap->w;
	height = heightMap->h;
	channels = heightMap->format->BytesPerPixel;

	unsigned char* inputData = (unsigned char*)heightMap->pixels;

	float x, y, z, u, v, nx, ny, nz;
	for (int row = 0; row < height; row++) {
		for (int collumn = 0; collumn < width; collumn++) {
			
			unsigned char redPixel = inputData[((row * width) + collumn) * channels];
			unsigned char greenPixel = inputData[((row * width) + collumn) * channels + 1];
			unsigned char bluePixel = inputData[((row * width) + collumn) * channels + 2];

			int meanPixelValue = (redPixel + greenPixel + bluePixel) / 3;
			//std::cout << "Mean colour: " << meanPixelValue << std::endl;

			x = ((float)collumn / (float)width - 1) * scale;
			y = (meanPixelValue / 255.0f) * hScale;
			z = ((float)row / (float)height - 1) * scale;
			u = ((float)collumn / (float)width - 1);
			v = ((float)row / (float)height - 1);
			//Need to fix normal calc
			nx = 0.0f;
			ny = 1.0f;
			nz = 0.0f;
			verticies.emplace_back(Vertex(x, y, z, u, v, nx, ny, nz));
		}
	}

	

	unsigned int c, n;
	for (int row = 0; row < height - 1; row++) {
		for (int collumn = 0; collumn < width - 1; collumn++) {
			c = row * width + collumn;
			n = (row + 1) * width + collumn;

			indecies.emplace_back(c);
			indecies.emplace_back(n);
			indecies.emplace_back(c + 1);
			indecies.emplace_back(c + 1);
			indecies.emplace_back(n);
			indecies.emplace_back(n + 1);
		}
	}

	/*//Generate vbo
	glCreateBuffers(1, &vboTerrain);
	glBindBuffer(GL_ARRAY_BUFFER, vboTerrain);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), (void*)&verticies[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	//Generate ibo
	glGenBuffers(1, &iboTerrain);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboTerrain);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(unsigned int), (void*)&indecies[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	*/
	//Cleanup
	SDL_FreeSurface(heightMap);
}

GE::Terrain::~Terrain()
{
}
