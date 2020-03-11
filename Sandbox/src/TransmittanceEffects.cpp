#include "TransmittanceEffects.h"

TransmittanceEffects::TransmittanceEffects()
{
	deltaTime = 0.0f;
	lastTime = 0.0f;
	uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformFarPlane = 0;

	skyboxLocation = 0;

	winX = 1366;
	winY = 768;
	projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
}

void TransmittanceEffects::calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}
	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void TransmittanceEffects::CreateShaders()
{
	//Using default shaders you can define your own shaders
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(constants::vShader, constants::fShader);
	shaderList.push_back(*shader1);
}

void TransmittanceEffects::RenderScene()
{
	glm::mat4 model;


	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0f, 2.0f, -2.5f));
	model = glm::scale(model, glm::vec3(2.f, 2.f, 2.f));
	model = glm::rotate(model, -90.0f * constants::GLOBAL_toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//get the uniform location from frag shader - samplercube

	//set 0 to th above
	sphere.RenderModel();
}

void TransmittanceEffects::RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	glViewport(0, 0, 1366, 768);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(viewMatrix, projectionMatrix);

	shaderList[0].UseShader();

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformModel = shaderList[0].GetModelLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);


	skyboxLocation = shaderList[0].GetSkyboxLocation();
	glUniform1i(skyboxLocation, 0);

	shaderList[0].SetTexture(1);

	shaderList[0].Validate();

	RenderScene();
}

void TransmittanceEffects::setWinDimensions(GLuint X, GLuint Y)
{
	winX = X;
	winY = Y;
}

void TransmittanceEffects::run()
{
	mainWindow = Window(winX, winY);
	mainWindow.Initialise();

	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);


	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);

	sphere = Model();
	sphere.LoadModel(model_pth);


	std::vector<std::string> skyboxFaces;
	//TODO: define a vector for the textures
	skyboxFaces.push_back(tex_rt);
	skyboxFaces.push_back(tex_lt);
	skyboxFaces.push_back(tex_tp);
	skyboxFaces.push_back(tex_bt);
	skyboxFaces.push_back(tex_bk);
	skyboxFaces.push_back(tex_ft);

	skybox = Skybox(skyboxFaces);

	//GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
	//	uniformSpecularIntensity = 0, uniformShininess = 0;
	
	//main loop
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;


		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		RenderPass(camera.calculateViewMatrix(), projection);

		mainWindow.swapBuffers();
	}
}
