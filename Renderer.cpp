#include "Renderer.h"

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	
	GLfloat verts[] = 
	{
		-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

	};


	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
	glUseProgram(programID);

	// MVP stuff
	MatrixID = glGetUniformLocation(programID, "MVP");

	ProjectionMatrix = mat4(1.0f);
	ViewMatrix = mat4(1.0f);

	// Model matrix : we will scale the triangle 1/4 both in x and y axes THEN translate it by 0.5 in x-axis and -0.5 in y-axis
	mat4 scaleMat = scale(0.25f, 0.25f, 0.0f);
	mat4 translateMat = translate(0.5f, -0.2f, 0.0f);
	mat4 rotateMat = rotate(60.0f, vec3(0, 0, 1));

	ModelMatrix = rotateMat * translateMat * scaleMat; 

	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix; 
}

void Renderer::Draw()
{
		glClear( GL_COLOR_BUFFER_BIT );
		
		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 6, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)* 6, (char*)(sizeof(float)* 3));
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
}

void Renderer::Cleanup()
{
    glDeleteBuffers(1, &vertexBufferID);
    glDeleteVertexArrays(1, &vertexArrayID);
    glDeleteProgram(programID);
}