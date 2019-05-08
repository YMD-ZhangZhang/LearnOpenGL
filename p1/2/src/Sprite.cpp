#include "Sprite.h"

Sprite::Sprite()
{
	this->createShader();
}

void Sprite::loadTexture(const char * url)
{
	//glActiveTexture(GL_TEXTURE0);

	_texture = new Texture2D(url);
	_texture->bindTexture();
	_texture->texImage2D();
	_texture->texParameteri();

	//_texture->dispose();
}

void Sprite::onRender(Camera* camera)
{
	// 使用shader
	this->_shader->use();

	// 根据实时位置生成顶点 并提交
	this->createVBO();
	this->createVAO();
	glBindVertexArray(this->_vao);

	// 绑定纹理
	_texture->bindTexture();

	// 绘制
	glDrawArrays(GL_TRIANGLES, 0, 6);

	Node::onRender(camera);
}

void Sprite::createShader()
{
	const char* vsPath = ".\\shader\\demo2vs.txt";
	const char* fsPath = ".\\shader\\demo2fs.txt";
	this->_shader = new ZShader(vsPath, fsPath);
	this->_shader->setUniform1i("material.diffuse", 0);
}

void Sprite::createVBO()
{
	// 坐标系 左上为0,0
	float screenWidth = (float)(Engine::getInstance()->getWidth());
	float screenHeight = (float)(Engine::getInstance()->getHeight());

	float x = (float)(this->getX());
	float y = (float)(this->getY());

	float width = (float)(this->getWidth());
	float height = (float)(this->getHeight());

	// 计算4个点
	float leftTopX = x / screenWidth * 2 - 1;
	float leftTopY = y / screenHeight * 2 + 1;

	float leftDownX = leftTopX;
	float leftDownY = leftTopY - height / screenHeight * 2;

	float rightTopX = leftTopX + width / screenWidth * 2;
	float rightTopY = leftTopY;

	float rightDownX = rightTopX;
	float rightDownY = rightTopY - height / screenHeight * 2;

	float vertices[] = 
	{
		leftDownX, leftDownY, 0.0f, 0.0f,// 左下
		rightTopX, rightDownY, 1.0f, 0.0f,// 右下
		leftTopX, leftTopY, 0.0f, 1.0f,// 左上

		leftTopX, leftTopY, 0.0f, 1.0f,// 左上
		rightTopX, rightTopY, 1.0f, 1.0f,// 右上
		rightDownX, rightDownY, 1.0f, 0.0f,// 右下
	};

	// VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// VBO base data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// dispose
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	this->_vbo = VBO;
}

void Sprite::createVAO()
{
	// 顶点数组对象 VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	// VBO add data 顶点坐标
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// VBO add data 纹理
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	this->_vao = VAO;
}
