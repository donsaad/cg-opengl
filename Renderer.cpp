#include "Renderer.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {
	Cleanup();
}

void Renderer::Initialize() {
	// Creating Vertex-Array-Object (VAO). Not used here, check the handout to see its importance.
	//VertexArrayID variable is defined in the Renderer.h file
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	///////////////////////////////////////////////////////////////////////////////////////////
	/// Start Drawing your primitive
	////////////////////////////////

	// Set the background color to blue
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	// [TODO] 1) create the data array (stored in RAM)
	GLfloat verts[] =
	{
		+0.0f, +1.0f, +0.0f,
		-1.0f, -1.0f, +0.0f,
		+1.0f, -1.0f, +0.0f
	};


	// [DONE step] 2) create a buffer object name(ID) holder. (initialized in Renderer.h)
	//  its name is "vertexBufferID"


	// [TODO] 3) reserve/generate a buffer object name(ID).
	glGenBuffers(1, &vertexBufferID);

	// [TODO] 4) set vertexbufferID as the current GL_ARRAY_BUFFER.
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	// [TODO] 5) allocate the mem in the GPU and copy the data from the RAM to the GPU,
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	// Use our shader
	glUseProgram(programID);
}

void Renderer::Draw() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(programID);

	// [TODO] 6) enable the desired attributes. (Please go to this section for more information about vertex attributes:
	glEnableVertexAttribArray(0);

	// [TODO] 7) specify the vertex-data format.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// [TODO] 8) Draw the triangle !
	// note that glDrawArrays, uses the currently bound BO in GL_ARRAY_BUFFER.
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// [TODO] 9) Disable the previously enabled attribute
	glDisableVertexAttribArray(0);
	// Binding will be written in the Draw function instead of the Initialize function if we want to draw more than one object
}

void Renderer::Cleanup() {
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteVertexArrays(1, &vertexArrayID); //the one we didn't used (will be discussed later)
	glDeleteProgram(programID);
}