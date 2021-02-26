#include "ModelRenderer.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace GE {

	ModelRenderer::ModelRenderer(Model* _model, Camera* _cam)
	{
		camera = _cam;
		posX = posY = posZ = 0.0f;
		rotX = rotY = rotZ = 0.0f;
		scaleX = scaleY = scaleZ = 1.0f;

		model = _model;
	}

	ModelRenderer::~ModelRenderer()
	{
	}

	void DisplayShaderCompilerError(GLuint _shaderID) {
		GLint msgLen = 0;

		glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &msgLen);

		if (msgLen > 1) {
			GLchar* msg = new GLchar[msgLen + 1];

			glGetShaderInfoLog(_shaderID, msgLen, NULL, msg);

			std::cerr << "Error compiling shader: " << msg << std::endl;

			delete[] msg;
		}
	}

	void ModelRenderer::Init()
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec3 vertexPos3D;\n"
			"in vec2 vUV;\n"
			"out vec2 uv;\n"
			"uniform mat4 transform;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main() {\n"
			"vec4 v = vec4(vertexPos3D.xyz, 1);\n"
			"v = projection * view * transform * v;\n"
			"gl_Position = v;\n"
			"uv = vUV;\n"
			"}\n" 
		};

		glShaderSource(vertexShader, 1, V_ShaderCode, NULL);

		glCompileShader(vertexShader);

		GLint isShaderCompiledOK = GL_FALSE;

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to complie vertex shader" << std::endl;
			DisplayShaderCompilerError(vertexShader);
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* F_ShaderCode[] = {
			"#version 140\n"
			"in vec2 uv;\n"
			"uniform sampler2D sampler;\n"
			"out vec4 fragmentColour;\n"
			"void main()\n"
			"{\n"
			"fragmentColour = texture(sampler, uv).rgba;\n"
			"}\n"
		};

		glShaderSource(fragmentShader, 1, F_ShaderCode, NULL);

		glCompileShader(fragmentShader);

		isShaderCompiledOK = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			std::cerr << "Unable to compile fragment shader" << std::endl;
			DisplayShaderCompilerError(fragmentShader);
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

		vertexPos3DLocation = glGetAttribLocation(programId, "vertexPos3D");

		if (vertexPos3DLocation == -1) {
			std::cerr << "Problem getting vertexPos3D" << std::endl;
		}

		vertexUVLocation = glGetAttribLocation(programId, "vUV");

		if (vertexUVLocation == -1) {
			std::cerr << "Problem getting vUV" << std::endl;
		}

		transformUniformID = glGetUniformLocation(programId, "transform");
		viewUniformID = glGetUniformLocation(programId, "view");
		projectionUniformID = glGetUniformLocation(programId, "projection");
		samplerID = glGetUniformLocation(programId, "sampler");

		//Model specific initialization
		glGenBuffers(1, &vboModel);
		glBindBuffer(GL_ARRAY_BUFFER, vboModel);

		glBufferData(GL_ARRAY_BUFFER, model->GetNumVerticies() * sizeof(Vertex), model->GetVerticies(), GL_STATIC_DRAW);
	}

	void ModelRenderer::Update()
	{
	}

	void ModelRenderer::Draw(Camera* _cam)
	{
		glEnable(GL_CULL_FACE);

		glm::mat4 transformationMat = glm::mat4(1.0f);

		transformationMat = glm::translate(transformationMat, glm::vec3(posX, posY, posZ));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		transformationMat = glm::rotate(transformationMat, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		transformationMat = glm::scale(transformationMat, glm::vec3(scaleX, scaleY, scaleZ));

		glm::mat4 viewMat = _cam->GetViewMatrix();
		glm::mat4 projectionMat = _cam->GetProjectMatrix();

		glUseProgram(programId);

		glUniformMatrix4fv(transformUniformID, 1, GL_FALSE, glm::value_ptr(transformationMat));
		glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, glm::value_ptr(projectionMat));

		
		glEnableVertexAttribArray(vertexPos3DLocation);

		glBindBuffer(GL_ARRAY_BUFFER, vboModel);

		glVertexAttribPointer(vertexPos3DLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));

		glEnableVertexAttribArray(vertexUVLocation);

		glVertexAttribPointer(vertexUVLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));

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

	void ModelRenderer::DrawTerrain(Terrain* _terrain)
	{
	}

	void ModelRenderer::DrawSkydome(Skydome* _skydome)
	{

	}

	void ModelRenderer::Destroy()
	{
		glDeleteProgram(programId);

		glDeleteBuffers(1, &vboModel);
	}
}