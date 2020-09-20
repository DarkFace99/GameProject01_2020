#include "Renderable.h"

extern unsigned int		shader;
glm::mat4				MVP;
Texture					blankTex;

//Camera-----------------------------------
glm::vec3				campos;
glm::vec3				camdir;
glm::vec3				camup;
float					camzoom;
float					camdegree;
glm::mat4				viewMatrix;
glm::mat4				projectionMatrix;


/*----------------------------------------------------Set Vertex Function----------------------------------------------------------------*/


/* Default constructor */
Vertex::Vertex()
{
	Vertex::position = glm::vec3(0, 0, 0);
	Vertex::color = glm::vec3(0, 0, 0);
	Vertex::texCoords = glm::vec2(0, 0);
}

/* Set constructor */
Vertex::Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 textureCoordinate) 
{
	Vertex::position = position;
	Vertex::color = color;
	Vertex::texCoords = textureCoordinate;
}

/* Get & Set Position function */
void Vertex::setPositionX(float x) { position.x = x; }
void Vertex::setPositionY(float y) { position.y = y; }
void Vertex::setPositionZ(float z) { position.z = z; }
void Vertex::SetPosition(glm::vec3 position) { Vertex::position = position; }
glm::vec3 Vertex::GetPosition() { return position; }
float Vertex::getPositionX() { return position.x; }

/* Get & Set Color function */
void Vertex::SetColorR(float r) { color.x = r; }
void Vertex::SetColorG(float g) { color.y = g; }
void Vertex::SetColorB(float b) { color.z = b; }
void Vertex::SetColor(glm::vec3 color) { Vertex::color = color; }
glm::vec3 Vertex::GetColor() { return color; }

/* Get & Set TextureCoordinate function */
void Vertex::SetTexCoordsU(float u) { Vertex::texCoords.x = u; }
void Vertex::SetTexCoordsV(float v) { Vertex::texCoords.y = v; }
void Vertex::SetTexCoords(glm::vec2 texCoords) { Vertex::texCoords = texCoords; }
glm::vec2 Vertex::GetTexCoords() { return texCoords; }
/*----------------------------------------------------Set Vertex Function----------------------------------------------------------------*/


/*----------------------------------------------------Texture Function----------------------------------------------------------------*/
Texture Renderable::LoadTexture(const char* filename) 
{
	Texture		aTex;

	GLubyte*	pData;
	int			texWidth, texHeight, channels;

	pData = SOIL_load_image(filename, &texWidth, &texHeight, &channels, SOIL_LOAD_AUTO);

	glGenTextures(1, &aTex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, aTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	GLint format = (channels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, pData);

	SOIL_free_image_data(pData);

	return aTex;
}
void Renderable::UnloadTexture(Texture texture) 
{
	glDeleteTextures(1, &texture);
}
/*----------------------------------------------------Texture Function----------------------------------------------------------------*/


/*----------------------------------------------------Mesh Function----------------------------------------------------------------*/
Mesh Renderable::LoadMesh(std::vector<Vertex> in_vertex) 
{
	Mesh aMesh;
	aMesh.vertex = in_vertex;

	glGenBuffers(1, &aMesh.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, aMesh.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, aMesh.vertex.size() * sizeof(Vertex), &aMesh.vertex[0].GetPosition(), GL_STATIC_DRAW);

	/*Put in Mesh data to buffer*/
	glGenVertexArrays(1, &aMesh.vao);
	glBindVertexArray(aMesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, aMesh.vertexBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));		//The starting point of the VBO, for the vertices
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(12));     //The starting point of color, 12 bytes away
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(24));

	glBindVertexArray(0);

	return aMesh;
}
void Renderable::DrawMesh(Mesh mesh)
{
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.vertex.size());

	glBindVertexArray(0);
}
void Renderable::UnloadMesh(Mesh mesh)
{
	glDeleteBuffers(1, &mesh.vertexBuffer);
	glDeleteVertexArrays(1, &mesh.vao);

	mesh.vertex.clear();
}
/*----------------------------------------------------Mesh Function----------------------------------------------------------------*/


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