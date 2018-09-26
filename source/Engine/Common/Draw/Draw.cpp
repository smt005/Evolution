
//#include "windows.h"
//#include <GL/gl.h>
//#include <GL/glu.h> 
#include "../../../ThirdParty/glew/include/GL/glew.h"

#include "Draw.h"
#include "../../Window.h"
#include "../Object/Mesh.h"
#include "Shader.h"

float _clearColor[4] = { 0.3f, 0.6f , 0.9f , 1.0f };

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

void Draw::draw(Mesh& mesh)
{
	static unsigned int program;

	if (program == 0) {
		program = Shader::getProgram("Shaders/Base.vert", "Shaders/Base.frag");
	}

	if (!mesh.hasVBO()) {
		mesh.initVBO();
	}

	static unsigned int cuttrentVertexesBufer = 0;

	if (mesh.bufferVertexes() != cuttrentVertexesBufer)
	{
		GLuint a_position = glGetAttribLocation(program, "a_position");
		GLuint a_texCoord = glGetAttribLocation(program, "a_texCoord");

		glBindBuffer(GL_ARRAY_BUFFER, mesh._buffer[0]);
		glEnableVertexAttribArray(a_position);
		glVertexAttribPointer(a_position, SHAPE_VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, mesh._buffer[1]);
		glEnableVertexAttribArray(a_texCoord);
		glVertexAttribPointer(a_texCoord, SHAPE_VERTEX_TEX_SIZE, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh._buffer[3]);

		_cuttrentBufer = mesh._buffer[3];
	}

	unsigned int textureId = 0;
	if (texture)
	{
		textureId = texture->id();
	}

	if (textureId != _cuttrentTexture)
	{
		GLuint u_color = glGetUniformLocation(_programBase, "u_color");
		GLuint s_baseMap = glGetUniformLocation(_programBase, "s_baseMap");

		float color[] = { 1.0, 1.0, 1.0, 1.0 };
		glUniform4fv(u_color, 1, color);

		glUniform1i(s_baseMap, 0);
		glBindTexture(GL_TEXTURE_2D, textureId);

		_cuttrentTexture = textureId;
	}

	glDrawElements(GL_TRIANGLES, mesh._countIndex, GL_UNSIGNED_SHORT, 0);
}