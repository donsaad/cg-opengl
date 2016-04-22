#include <gl/glew.h>
#include "shader.hpp"
#include <glm/gtx/transform.hpp>
using namespace glm;
#pragma once

class Renderer
{
    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint programID;
	
	GLuint MatrixID;
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	mat4 ModelMatrix;
	mat4 MVP;

public:
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
    void Cleanup();
};
