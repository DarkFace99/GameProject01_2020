#include "Renderable.h"

/*----------------------------------------------------Set Vertex Function----------------------------------------------------------------*/

/* Default constructor */
Vertex::Vertex()
{
	Vertex::position = glm::vec3(0, 0, 0);
	Vertex::color = glm::vec3(0, 0, 0);
	Vertex::textureCoordinate = glm::vec2(0, 0);
}

/* Set constructor */
Vertex::Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 textureCoordinate) 
{
	Vertex::position = position;
	Vertex::color = color;
	Vertex::textureCoordinate = textureCoordinate;
}

/* Get & Set Position function */
void Vertex::setPositionX(float x) { position.x = x; }
void Vertex::setPositionY(float y) { position.y = y; }
void Vertex::setPositionZ(float z) { position.z = z; }
void Vertex::SetPosition(glm::vec3 position) { Vertex::position = position; }
glm::vec3 Vertex::GetPosition() { return position; }

/* Get & Set Color function */
void Vertex::SetColorR(float r) { color.x = r; }
void Vertex::SetColorG(float g) { color.y = g; }
void Vertex::SetColorB(float b) { color.z = b; }
void Vertex::SetColor(glm::vec3 color) { Vertex::color = color; }
glm::vec3 Vertex::GetColor() { return color; }

/* Get & Set TextureCoordinate function */
void Vertex::SetTextureCoordinateU(float u) { Vertex::textureCoordinate.x = u; }
void Vertex::SetTextureCoordinateV(float v) { Vertex::textureCoordinate.y = v; }
void Vertex::SetTextureCoordinate(glm::vec2 textureCoordinate) { Vertex::textureCoordinate = textureCoordinate; }
glm::vec2 Vertex::GetTextureCoordinate() { return textureCoordinate; }
/*----------------------------------------------------Set Vertex Function----------------------------------------------------------------*/




/*----------------------------------------------------Set Renderer Function----------------------------------------------------------------*/
void Renderable::SetRendererMode(int mode, float alpha) 
{
	/*Set the viewport of the screen. Lower Left coner will be (0,0) and the dimension will be SCREEN_WIDTH and SCREEN_HEIGTH*/
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGTH);
	glUseProgram(shader);

	/*Set the render mode between Texture and Solid Color*/
	glUniform1i(glGetUniformLocation(shader, "mode"), mode);
	glUniform1f(glGetUniformLocation(shader, "alpha"), alpha);

	// default setting
	SetTexture(blankTex, 0.0f, 0.0f);
	SetTransform(glm::mat4(1.0f));
}
void Renderable::SetTexture(Texture texture, float offsetX, float offsetY) 
{
	glUniform1f(glGetUniformLocation(shader, "offsetX"), offsetX);
	glUniform1f(glGetUniformLocation(shader, "offsetY"), offsetY);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader, "tex1"), 0);
}
void Renderable::SetTransform(const glm::mat4& modelMat) 
{
	/*Set transform of the objects relative to camera*/
	MVP = projectionMatrix * viewMatrix * modelMat;
	glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);
}
/*----------------------------------------------------Set Renderer Function----------------------------------------------------------------*/