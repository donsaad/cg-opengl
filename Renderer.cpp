#include "Renderer.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {
	Cleanup();
}

void Renderer::Initialize() {

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glClearColor(0.0f, 0.23f, 0.4f, 1.0f);

	GLfloat verts[] =
	{
		// triangle
		+1.0f, +0.0f, +0.0f, 1.0f, 0.0f, 0.0f,
		+0.5f, +1.0f, +0.0f, 1.0f, 0.0f, 0.0f,
		+0.0f, +0.0f, +0.0f, 1.0f, 0.0f, 0.0f,

		// square as 2 triangles
		-1.0f, +0.0f, +0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, +1.0f, +0.0f, 0.0f, 0.0f, 1.0f,
		-0.0f, +1.0f, +0.0f, 0.0f, 0.0f, 1.0f,

		+0.0f, +0.0f, +0.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, +0.0f, +0.0f, 0.0f, 0.0f, 1.0f,
		-0.0f, +1.0f, +0.0f, 0.0f, 0.0f, 1.0f,

	};


	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	glUseProgram(programID);

}

void Renderer::Draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 6, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 6, (char*)(sizeof(float)* 3));

	glDrawArrays(GL_TRIANGLES, 0, 9); // 9 vertices

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Renderer::Cleanup() {
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteProgram(programID);
}