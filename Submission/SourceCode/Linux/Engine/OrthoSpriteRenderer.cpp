#include "OrthoSpriteRenderer.h"

namespace GE {
	void OrthoSpriteRenderer::Init()
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			" in vec4 vertex;\n"
			"out vec2 texCoords;\n"
			"uniform mat4 model;\n"
			"uniform mat4 projection;\n"
			"void main() {\n"
			"texCoords = vertex.zw;\n"
			"gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
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
			"in vec2 texCoords;\n"
			"out vec4 colour;\n"
			"uniform sampler2D image;\n"
			"uniform vec3 spriteColour;\n"
			"void main()\n"
			"{\n"
			"colour = vec4(spriteColour, 1.0) * texture(image, texCoords);\n"
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

		programID = glCreateProgram();

		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);

		glLinkProgram(programID);

		GLint isProgramLinked = GL_FALSE;

		glGetProgramiv(programID, GL_LINK_STATUS, &isProgramLinked);
		if (isProgramLinked != GL_TRUE) {
			std::cerr << "Failed to link program" << std::endl;
		}

		vertexLocation = glGetAttribLocation(programID, "vertex");

		if (vertexLocation == -1) {
			std::cerr << "Problem getting vertexLocation" << std::endl;
		}
		modelUniformLocation = glGetUniformLocation(programID, "model");
		projectionUniformLocation = glGetUniformLocation(programID, "projection");
		imageUniformLocation = glGetUniformLocation(programID, "image");
		spriteColourUniformLocation = glGetUniformLocation(programID, "spriteColour");

		//Model specific initialization
		unsigned int VBO;
		float vertices[] = {
			// pos      // tex
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &this->quadVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(this->quadVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void OrthoSpriteRenderer::Update()
	{
	}

	void OrthoSpriteRenderer::Draw(glm::vec2 _position, glm::vec2 _size, float _rotation, glm::vec3 _colour)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(_position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
		model = glm::rotate(model, glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));

		model = glm::scale(model, glm::vec3(_size, 1.0f));

		glUseProgram(programID);
		glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(orthProjection));
		glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(spriteColourUniformLocation, 1, &_colour[0]);

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(imageUniformLocation, 0);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureName());

		glBindVertexArray(this->quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void OrthoSpriteRenderer::Destroy()
	{
	}
}
