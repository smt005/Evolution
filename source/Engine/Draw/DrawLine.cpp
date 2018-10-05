
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

void DrawLine::set(const float* const posFirst, const float* const posSecond)
{
	if (_data) {
		delete[] _data;
		_data = nullptr;
	}

	if (!_data) {
		_count = 2;
		_data = new float[_count * 3];
	}

	_data[0] = posFirst[0];
	_data[1] = posFirst[1];
	_data[2] = posFirst[2];

	_data[3] = posSecond[0];
	_data[4] = posSecond[1];
	_data[5] = posSecond[2];
}

void DrawLine::prepare()
{
	if (lineShader.program == 0) {
		lineShader.program = Shader::getProgram("Shaders/LineMatrix.vert", "Shaders/LineMatrix.frag");

		if (!lineShader.program) {
			return;
		}

		lineShader.a_position = glGetUniformLocation(lineShader.program, "u_matrix");
		lineShader.u_matrix = glGetUniformLocation(lineShader.program, "u_matrix");
		lineShader.u_color = glGetUniformLocation(lineShader.program, "u_color");
	}

	glUseProgram(lineShader.program);
	glUniformMatrix4fv(lineShader.u_matrix, 1, GL_FALSE, Camera::current.matProjectViewFloat());

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(lineShader.a_position);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void DrawLine::draw()
{
	glUniform4fv(lineShader.u_color, 1, _color.getDataPtr());
	glLineWidth(_lineWidth);

	glVertexAttribPointer(lineShader.a_position, 3, GL_FLOAT, GL_FALSE, 0, _data);
	glDrawArrays(GL_LINES, 0, _count);
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
