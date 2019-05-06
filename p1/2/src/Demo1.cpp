#include "Demo1.h"

Demo1::Demo1()
{
	this->init = false;
	this->vsPath = ".\\shader\\vs.txt";
	this->fsPath = ".\\shader\\fs.txt";
}

void Demo1::begin()
{
	ZOpenGL::init(this);
}

void Demo1::onRenderLoop(GLFWwindow * window)
{
	if (!this->init)
	{
		this->init = true;
		this->shaderObj = new ZShader(vsPath, fsPath);
	}

	this->processInput(window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	onRender(shaderObj);
}

void Demo1::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Demo1::onRender(ZShader * shaderObj)
{
	unsigned int boxVBO = createBoxVBO();
	unsigned int objVAO = createObjVAO(boxVBO);
	renderObj(objVAO, shaderObj);
}

unsigned int Demo1::createBoxVBO()
{
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	// VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// VBO base data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	return VBO;
}

unsigned int Demo1::createObjVAO(unsigned int boxVBO)
{
	// ����������� VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
	// VBO add aata ��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// VBO add data ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// VBO add data ����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	return VAO;
}

void Demo1::loadDiffuseTexture()
{
	Texture2D t1(".\\texture\\container2.png");
	glActiveTexture(GL_TEXTURE0);
	t1.bindTexture();
	t1.texImage2D();
	t1.texParameteri();
	t1.dispose();
}

void Demo1::loadSpecularTexture()
{
	Texture2D t1(".\\texture\\container2_specular.png");
	glActiveTexture(GL_TEXTURE1);
	t1.bindTexture();
	t1.texImage2D();
	t1.texParameteri();
	t1.dispose();
}

void Demo1::renderObj(unsigned int objVAO, ZShader * shader)
{
	shader->use();
	glBindVertexArray(objVAO);

	// ģ�;���
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	shader->setUniformMatrix4fv("model", 1, GL_FALSE, glm::value_ptr(model));

	// �۲����
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	shader->setUniformMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(view));

	// ͶӰ����
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)480 / 320, 0.1f, 100.0f);
	shader->setUniformMatrix4fv("projection", 1, GL_FALSE, glm::value_ptr(projection));

	// base
	shader->setUniform3f("lightPos", 1.2f, 1.0f, 2.0f);
	shader->setUniform3f("viewPos", 0.0f, 0.0f, 3.0f);

	// light
	shader->setUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
	shader->setUniform3f("light.diffuse", 0.8f, 0.8f, 0.8f);
	shader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);

	// material
	shader->setUniform1i("material.diffuse", 0);
	shader->setUniform1i("material.specular", 1);
	shader->setUniform1i("material.shininess", 50.0f);

	// ͼ��ת
	//stbi_set_flip_vertically_on_load(true);

	// ��ͼ =====
	loadDiffuseTexture();
	loadSpecularTexture();

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
