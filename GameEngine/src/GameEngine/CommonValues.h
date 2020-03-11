#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GameEngine/Core/Log.h>


//glPipeline
#include "glPipeline/Camera.h"
#include "glPipeline/Material.h"
#include "glPipeline/Mesh.h"
#include "glPipeline/Model.h"
#include "glPipeline/Shader.h"
#include "glPipeline/Skybox.h"
#include "glPipeline/Texture.h"
#include "glPipeline/Windows.h"


namespace mainWIN {

	GLuint winX = 1366;
	GLuint winY = 768;

	inline void setX(GLuint X) { winX = X; }
	inline void setY(GLuint Y) { winY = Y; }
}