
#include "../../../ThirdParty/glew/include/GL/glew.h"

#include "Draw.h"
#include "Camera.h"
#include "../../Window.h"
#include "../Object/Mesh.h"
#include "Shader.h"

float _clearColor[4] = { 0.3f, 0.6f , 0.9f , 1.0f };
unsigned int program = 0;

void Draw::setClearColor(const float r, const float g, const float b, const float a)
{
	_clearColor[0] = r;
	_clearColor[1] = g;
	_clearColor[2] = b;
	_clearColor[3] = a;

	glClearColor(r, g, b, a);
}

const float * const Draw::getClearColor()
{
	return _clearColor;
}

void Draw::clearColor()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Draw::prepare()
{
	int widthScreen = Window::width();
	int heightScreen = Window::height();
	glViewport(0.0, 0.0, widthScreen, heightScreen);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (program == 0) {
		program = Shader::getProgram("Shaders/Base.vert", "Shaders/Base.frag");
		glUseProgram(program);
	}

	GLuint u_matProjectionView = glGetUniformLocation(program, "u_matProjectionView");
	glUniformMatrix4fv(u_matProjectionView, 1, GL_FALSE, Camera::current.matPV());
}

float kRed = 0.001;
float red = 0.3f;
float kGreen = 0.002;
float green = 0.6f;
float kBlue = 0.001;
float blue = 0.9f;

void Draw::drawBackround()
{
	setClearColor(red, green, blue, 1.0f);

	{
		red += kRed;

		if (red > 1.0f) {
			kRed = -0.001;
		}

		if (red < 0.0f) {
			kRed = 0.001;
		}
	}

	{
		green += kGreen;

		if (green > 1.0f) {
			kGreen = -0.001;
		}

		if (green < 0.0f) {
			kGreen = 0.001;
		}
	}

	{
		blue += kBlue;

		if (blue > 1.0f) {
			kBlue = -0.001;
		}

		if (blue < 0.0f) {
			kBlue = 0.001;
		}
	}
}

void Draw::drawTriangle()
{

}

void Draw::draw(Mesh& mesh, glm::mat4x4& matrix)
{
	if (program == 0) {
		return;
	}

	GLuint u_matViewModel = glGetUniformLocation(program, "u_matViewModel");
	glUniformMatrix4fv(u_matViewModel, 1, GL_FALSE, glm::value_ptr(matrix));

	static unsigned int cuttrentBufferIndexes;

	if (!mesh.hasVBO()) {
		mesh.initVBO();
	}

	if (cuttrentBufferIndexes != mesh.bufferIndexes())
	{
		GLuint a_position = glGetAttribLocation(program, "a_position");
		GLuint a_texCoord = glGetAttribLocation(program, "a_texCoord");

		glBindBuffer(GL_ARRAY_BUFFER, mesh.bufferVertexes());
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, mesh.bufferTexCoords());
		glEnableVertexAttribArray(a_texCoord);
		glVertexAttribPointer(a_texCoord, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.bufferIndexes());

		cuttrentBufferIndexes = mesh.bufferIndexes();
	}

	glDrawElements(GL_TRIANGLES, mesh.countIndex(), GL_UNSIGNED_SHORT, 0);
}