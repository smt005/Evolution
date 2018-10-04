
#include "glew/include/GL/glew.h"

#include "Draw.h"
#include "Camera.h"
#include "Shader.h"

#include "DrawLine.h"

//	DrawLine

using namespace draw;

struct {
	unsigned int program = 0;
	GLuint u_matProjectionView = 0;
	GLuint a_position = 0;
	GLuint u_matrix = 0;
	GLuint u_color = 0;
} lineShader;

void DrawLine::prepare()
{
	if (lineShader.program == 0) {
		lineShader.program = Shader::getProgram("Shaders/LineMatrix.vert", "Shaders/LineMatrix.frag");

		if (!lineShader.program) {
			return;
		}

		lineShader.a_position = 0;
		glBindAttribLocation(lineShader.program, lineShader.a_position, "a_position");

		lineShader.u_matrix = glGetUniformLocation(lineShader.program, "u_matrix");
		lineShader.u_color = glGetUniformLocation(lineShader.program, "u_color");

		glUseProgram(lineShader.program);
	}

	glUniformMatrix4fv(lineShader.u_matrix, 1, GL_FALSE, Camera::current.matProjectViewFloat());

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void DrawLine::draw()
{
	glUniform4fv(lineShader.u_color, 1, _color.getDataPtr());
	glLineWidth(5.0f);

	//GLfloat line[] = { 0.0f, 0.0f , 0.0f, 10.0f, 10.0f , 10.0f };
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, line);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, _data);
	glDrawArrays(GL_LINES, 0, 2);
}

//	DrawGrid

DrawGrid::DrawGrid()
	: _colorX(Color::RED)
	, _colorY(Color::GREEN)
	, _colorZ(Color::BLUE)
{

}

void DrawGrid::draw()
{

}
