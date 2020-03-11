#pragma once
#include "enpch.h"

#include "GameEngine.h"

//import EPCH implementations
#include "GameEngine/CommonValues.h"


class TransmittanceEffects
{
public:
	TransmittanceEffects();
	virtual ~TransmittanceEffects() = default;

	//SHADERS
	//static const char* vShader = "Shaders/shader.vert";
	//static const char* fShader = "Shaders/shader.frag";

private:
	GLuint uniformProjection, uniformModel, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess, uniformFarPlane;
	GLfloat deltaTime;
	GLfloat lastTime;

	//WindowSize
	GLuint winX, winY;

	Window mainWindow;
	std::vector<Shader> shaderList;
	Camera camera;
	//Texture dirtTexture;

	Material shinyMaterial;
	Material dullMaterial;
	Model sphere;
	Skybox skybox;
	GLuint skyboxLocation;

	//Perspective projection
	glm::mat4 projection;

	//model loc
	const char* model_pth = "Models/MIT-Sphere/sphere.obj";
	const char* tex_ft = "Textures/bluecloud_ft.jpg";
	const char* tex_bk = "Textures/bluecloud_bk.jpg";
	const char* tex_rt = "Textures/bluecloud_rt.jpg";
	const char* tex_lt = "Textures/bluecloud_lt.jpg";
	const char* tex_tp = "Textures/bluecloud_up.jpg";
	const char* tex_bt = "Textures/bluecloud_dn.jpg";

	void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
		unsigned int vLength, unsigned int normalOffset);

	void CreateShaders();
	void RenderScene();
	void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	void setWinDimensions(GLuint X, GLuint Y);

	//Test
	void run();
};

