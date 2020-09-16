#include "Renderable.h"

/* Vertex function definition */


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
