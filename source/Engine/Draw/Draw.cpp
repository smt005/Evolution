
#include "glew/include/GL/glew.h"

#include "Draw.h"
#include "Camera.h"
#include "Window.h"
#include "Shader.h"
#include "Object/Mesh.h"
#include "Object/Shape.h"
#include "Object/Model.h"
#include "Object/Object.h"
#include "Object/Glider.h"
#include "Object/Map.h"
#include "Object/ShapeTriangles.h"
#include "Object/Texture.h"

float _clearColor[4] = { 0.3f, 0.6f , 0.9f , 1.0f };
unsigned int program = 0;
TexturePtr texture;
unsigned int curentBufer = 0;
unsigned int currentTexture = 0;

struct {
	unsigned int program = 0;
	GLuint u_matProjectionView = 0;
	GLuint u_matViewModel = 0;
	GLuint a_position = 0;
	GLuint a_texCoord = 0;
	GLuint s_baseMap = 0;
} baseShader;

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

void Draw::viewport()
{
	int widthScreen = Window::width();
	int heightScreen = Window::height();
	glViewport(0, 0, widthScreen, heightScreen);
}

void Draw::prepare()
{
	if (baseShader.program == 0) {
		baseShader.program = Shader::getProgram("Shaders/Base.vert", "Shaders/Base.frag");
	
		if (!baseShader.program) {
			return;
		}

		baseShader.u_matProjectionView = glGetUniformLocation(baseShader.program, "u_matProjectionView");
		baseShader.u_matViewModel = glGetUniformLocation(baseShader.program, "u_matViewModel");

		baseShader.a_position = glGetAttribLocation(baseShader.program, "a_position");
		baseShader.a_texCoord = glGetAttribLocation(baseShader.program, "a_texCoord");

		baseShader.s_baseMap = glGetUniformLocation(baseShader.program, "s_baseMap");
	}

	glUseProgram(baseShader.program);
	glUniformMatrix4fv(baseShader.u_matProjectionView, 1, GL_FALSE, Camera::current.matPV());

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableVertexAttribArray(baseShader.a_position);
	glEnableVertexAttribArray(baseShader.a_texCoord);

	curentBufer = 0;
	currentTexture = 0;
}

void Draw::drawTriangleExample()
{
	GLfloat vVertices[] = {	0.0f, 5.0f, 0.0f,
							-50.0f, -50.0f, 0.0f,
							50.0f, -50.0f, 0.0f };

	glViewport(0, 0, Window::width(), Window::height());

	if (program == 0) {
		program = Shader::getProgram("Shaders/TriangleExample.vert", "Shaders/TriangleExample.frag");
	}

	GLint u_matProjectionView = glGetUniformLocation(program, "u_matProjectionView");
	GLuint u_matViewModel = glGetUniformLocation(program, "u_matViewModel");
	GLuint a_position = glGetAttribLocation(program, "a_position");
	
	{

		//glm::mat4x4 matrix(1.0f);
		//glUniformMatrix4fv(u_matProjectionView, 1, GL_FALSE, glm::value_ptr(matrix));
		glUniformMatrix4fv(u_matProjectionView, 1, GL_FALSE, Camera::current.matPV());
	}

	{
		
		glm::mat4x4 matrix(1.0f);
		matrix = glm::translate(matrix, glm::vec3(0.5f, 0.5f, 0.0f));
		glUniformMatrix4fv(u_matViewModel, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	glUseProgram(program);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	//glEnableVertexAttribArray(a_position);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Draw::draw(Mesh& mesh)
{
	if (!mesh.hasVBO()) {
		if (!mesh.initVBO()) return;
	}

	if (curentBufer != mesh.bufferIndexes())
	{
		curentBufer = mesh.bufferIndexes();

		glBindBuffer(GL_ARRAY_BUFFER, mesh.bufferVertexes());
		//glEnableVertexAttribArray(baseShader.a_position);
		glVertexAttribPointer(baseShader.a_position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, mesh.bufferTexCoords());
		//glEnableVertexAttribArray(baseShader.a_texCoord);
		glVertexAttribPointer(baseShader.a_texCoord, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.bufferIndexes());
	}

	glDrawElements(GL_TRIANGLES, mesh.countIndex(), GL_UNSIGNED_SHORT, 0);
}

void Draw::draw(Model& model)
{
	unsigned int textureId = model.textureId();
	if (currentTexture != textureId)
	{
		currentTexture = textureId;
		
		glUniform1i(baseShader.s_baseMap, 0);
		glBindTexture(GL_TEXTURE_2D, currentTexture);
	}

	Mesh& mesh = model.getMesh();
	draw(mesh);
}

void Draw::draw(Object& object)
{	
	const glm::mat4x4& matrix = object.getMatrix();
	glUniformMatrix4fv(baseShader.u_matViewModel, 1, GL_FALSE, glm::value_ptr(matrix));

	Model& model = object.getModel();
	draw(model);
}

void Draw::draw(Map& map)
{
	for (auto& object : map._objects) {
		if (object->visible()) {
			draw(*object);
		}
	}

	for (auto& glider : map._gliders) {
		if (glider->visible()) {
			draw(*glider);
		}
	}
}

void Draw::draw(ShapeTriangles& shape, const glm::mat4x4& matrix)
{
	glUniformMatrix4fv(baseShader.u_matViewModel, 1, GL_FALSE, glm::value_ptr(matrix));

	if (!texture) {
		//texture = std::make_shared<Texture>("Textures/Cell.png", true);
		texture = std::make_shared<Texture>("Textures/CellNoAlpha.png", true);
	}

	if (!shape.hasVBO()) {
		if (!shape.initVBO()) return;
	}

	if (curentBufer != shape.bufferVertexes())
	{
		curentBufer = shape.bufferVertexes();

		glUniform1i(baseShader.s_baseMap, 0);
		glBindTexture(GL_TEXTURE_2D, texture->id());

		glBindBuffer(GL_ARRAY_BUFFER, shape.bufferVertexes());
		glEnableVertexAttribArray(baseShader.a_position);
		glVertexAttribPointer(baseShader.a_position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		glBindBuffer(GL_ARRAY_BUFFER, shape.bufferTexCoords());
		glEnableVertexAttribArray(baseShader.a_texCoord);
		glVertexAttribPointer(baseShader.a_texCoord, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	}

	glDrawArrays(GL_TRIANGLES, 0, shape.countVertex());
}
