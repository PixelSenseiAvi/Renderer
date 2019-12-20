#pragma once

#include <vector>

#include "GameEngine/CommonValues.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Mesh.h"
#include "GameEngine/glPipeline/Shader.h"

class Skybox
{
public:
	Skybox();

	Skybox(std::vector<std::string> faceLocations);

	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~Skybox();

private:
	Mesh* skyMesh;
	Shader* skyShader;

	GLuint textureId;
	GLuint uniformProjection, uniformView;
};

