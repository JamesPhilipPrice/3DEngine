#include "WaterRenderer.h"
#include <glm/gtc/type_ptr.hpp>

namespace GE {
	WaterRenderer::WaterRenderer(float _width, float _height, int _vertexDensity, float _baseWaterLevel) {
		//Set the model scale
		scaleX = scaleY = scaleZ = 1.0f;
		posX = -_width / 2.0f;
		posY = _baseWaterLevel;
		posZ = -_height / 2.0f;

		std::vector<Vertex> vertices;
		std::vector<int> indices;

		//Generate vertices
		float x, y, z, u, v, nx, ny, nz;
		for (int row = 0; row < _vertexDensity; row++) {
			for (int collumn = 0; collumn < _vertexDensity; collumn++) {

				x = ((float)collumn / (float)_vertexDensity) * _width;
				y = 0.0f;
				z = ((float)row / (float)_vertexDensity) * _height;
				u = ((float)collumn / (float)_vertexDensity);
				v = ((float)row / (float)_vertexDensity);
				//Need to fix normal calc
				nx = 0.0f;
				ny = 1.0f;
				nz = 0.0f;
				vertices.emplace_back(Vertex(x, y, z, u, v, nx, ny, nz));
			}
		}

		//Generate indices
		unsigned int c, n;
		for (int row = 0; row < _vertexDensity - 1; row++) {
			for (int collumn = 0; collumn < _vertexDensity - 1; collumn++) {
				c = row * _vertexDensity + collumn;
				n = (row + 1) * _vertexDensity + collumn;

				indices.emplace_back(c);
				indices.emplace_back(n);
				indices.emplace_back(c + 1);
				indices.emplace_back(c + 1);
				indices.emplace_back(n);
				indices.emplace_back(n + 1);
			}
		}

		//Create vert list that cna be pushed to the model
		std::vector<Vertex> pushVerts;
		for (int i = 0; i < indices.size(); i++) {
			pushVerts.emplace_back(vertices[indices[i]]);
		}

		//Push them
		model = new Model();
		model->SetVerticies(pushVerts);

	}

	void WaterRenderer::Init() {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec4 vertexPosition;\n"
			"in vec2 uvCoordinates;\n"
			"in vec3 vertexNormal;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"uniform float gameTime;\n"
			"out vec2 out_uv;\n"
			"out vec3 out_normal;\n"
			"out vec3 fragPosition;\n"
			"void main() {\n"
			"float waveHeight = (sin(vertexPosition.x + gameTime) + cos(vertexPosition.z + gameTime)) * 0.09;\n"
			"gl_Position = projection * view * model * vec4(vertexPosition.x, vertexPosition.y + waveHeight, vertexPosition.zw);\n"
			"out_uv = uvCoordinates;\n"
			"out_normal = vec3(model * vec4(vertexNormal, 1.0f));\n"
			"fragPosition = vec3(model * vertexPosition);\n"
			"}\n"
		};

		glShaderSource(vertexShader, 1, V_ShaderCode, NULL);

		glCompileShader(vertexShader);

		GLint isShaderCompiledOK = GL_FALSE;

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to complie vertex shader" << std::endl;
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* F_ShaderCode[] = {
			"#version 140\n"
			"in vec2 out_uv;\n"
			"in vec3 fragPosition;\n"
			"in vec3 out_normal;\n"
			"out vec4 fragmentColour;\n"
			"uniform sampler2D sampler;\n"
			"uniform vec3 lightColour;\n"
			"uniform vec3 lightPosition;\n"
			"uniform vec3 viewPosition;\n"
			"void main()\n"
			"{\n"
			"float ambientStrength = 0.2f;\n"
			"vec3 ambient = ambientStrength * lightColour;\n"
			"vec3 normal = normalize(out_normal);\n"
			"vec3 lightDirection = normalize(lightPosition - fragPosition);\n"
			"float diff = max(dot(normal, lightDirection), 0.0f);\n"
			"vec3 diffuse = diff * lightColour;\n"
			"float specularStrength = 0.1f;\n"
			"vec3 viewDir = normalize(viewPosition - fragPosition);\n"
			"vec3 reflectDirection = reflect(-lightDirection, normal);\n"
			"float spec = pow(max(dot(viewDir, reflectDirection), 0.0f), 32);\n"
			"vec3 specular = specularStrength * spec * lightColour;\n"
			"vec3 textureColour = texture(sampler, out_uv).xyz;\n"
			"vec3 result = (ambient + diffuse) * textureColour + specular;\n"
			"fragmentColour = vec4(result, 1.0f);\n"
			"}\n"
		};

		glShaderSource(fragmentShader, 1, F_ShaderCode, NULL);

		glCompileShader(fragmentShader);

		isShaderCompiledOK = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to compile fragment shader" << std::endl;
			return;
		}

		programId = glCreateProgram();

		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);

		glLinkProgram(programId);

		GLint isProgramLinked = GL_FALSE;

		glGetProgramiv(programId, GL_LINK_STATUS, &isProgramLinked);
		if (isProgramLinked != GL_TRUE) {
			std::cerr << "Failed to link program" << std::endl;
		}

		vertexPos3DLocation = glGetAttribLocation(programId, "vertexPosition");

		if (vertexPos3DLocation == -1) {
			std::cerr << "Problem getting vertexPosition" << std::endl;
		}

		vertexUVLocation = glGetAttribLocation(programId, "uvCoordinates");

		if (vertexUVLocation == -1) {
			std::cerr << "Problem getting uvCoordinates" << std::endl;
		}

		vertexNormalLocation = glGetAttribLocation(programId, "vertexNormal");

		if (vertexNormalLocation == -1) {
			std::cerr << "Problem getting vertexNormal" << std::endl;
		}

		transformUniformID = glGetUniformLocation(programId, "model");
		viewUniformID = glGetUniformLocation(programId, "view");
		projectionUniformID = glGetUniformLocation(programId, "projection");
		gameTimeUniformID = glGetUniformLocation(programId, "gameTime");
		samplerID = glGetUniformLocation(programId, "sampler");
		lightColID = glGetUniformLocation(programId, "lightColour");
		lightPosID = glGetUniformLocation(programId, "lightPosition");
		viewPosID = glGetUniformLocation(programId, "viewPosition");

		//Model specific initialization
		glGenBuffers(1, &vboModel);
		glBindBuffer(GL_ARRAY_BUFFER, vboModel);

		glBufferData(GL_ARRAY_BUFFER, model->GetNumVerticies() * sizeof(Vertex), model->GetVerticies(), GL_STATIC_DRAW);
	}

	void WaterRenderer::Update() {

	}

	void WaterRenderer::Draw(Camera* _cam) {
		glEnable(GL_CULL_FACE);

		glm::mat4 transformationMat = glm::mat4(1.0f);

		transformationMat = glm::translate(transformationMat, glm::vec3(posX, posY, posZ));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		transformationMat = glm::scale(transformationMat, glm::vec3(scaleX, scaleY, scaleZ));

		glm::mat4 viewMat = _cam->GetViewMatrix();
		glm::mat4 projectionMat = _cam->GetProjectMatrix();

		//TEST LIGHT CODE
		glm::vec3 lightCol = glm::vec3(1.0, 0.85, 0.85);
		glm::vec3 lightPos = glm::vec3(100.0, 5.0, 100.0);

		glUseProgram(programId);

		glUniformMatrix4fv(transformUniformID, 1, GL_FALSE, glm::value_ptr(transformationMat));
		glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, glm::value_ptr(projectionMat));
		glUniform1f(gameTimeUniformID, gameTime);
		glUniform3fv(lightColID, 1, &lightCol[0]);
		glUniform3fv(lightPosID, 1, &lightPos[0]);
		glUniform3fv(viewPosID, 1, &_cam->GetPos()[0]);


		glEnableVertexAttribArray(vertexPos3DLocation);

		glBindBuffer(GL_ARRAY_BUFFER, vboModel);

		glVertexAttribPointer(vertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

		glEnableVertexAttribArray(vertexUVLocation);

		glVertexAttribPointer(vertexUVLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

		glEnableVertexAttribArray(vertexNormalLocation);

		glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, nx));

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(samplerID, 0);
		glBindTexture(GL_TEXTURE_2D, material->GetTextureName());

		glDrawArrays(GL_TRIANGLES, 0, model->GetNumVerticies());

		glDisableVertexAttribArray(vertexPos3DLocation);
		glDisableVertexAttribArray(vertexUVLocation);

		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisable(GL_CULL_FACE);
	}

	void WaterRenderer::Destroy() {

	}

}
