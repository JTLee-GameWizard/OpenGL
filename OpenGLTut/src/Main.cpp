#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>

const int windowWidth = 1280;
const int windowHeight = 720;

void ReadShader(std::string& OutSrc, const std::string& Dir)
{
	std::ifstream SrcInFileStream{Dir};
	std::string Read;
	while (std::getline(SrcInFileStream, Read))
	{
		OutSrc += Read;
		OutSrc += '\n';
	}
}

void GetShaderCompliationMsg(unsigned int Shader)
{
	int Success;
	char Log[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &Success);
	if (!Success)
	{
		glGetShaderInfoLog(Shader, 512, nullptr, Log);
		std::cout << "Shader Compilation Error: " << Log << std::endl;
	}
}

void GetShaderProgramLinkMsg(unsigned int Program)
{
	int Success;
	char Log[512];
	glGetProgramiv(Program, GL_LINK_STATUS, & Success);
	if (!Success)
	{
		glGetProgramInfoLog(Program, 512, NULL, Log);
		std::cout << "program linking error: " << Log << std::endl;
	}
}

int main()
{
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGLRenderWindow", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

	float vertices[] = {
		//position            //uv
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	std::string VertexShaderSrcStr;
	ReadShader(VertexShaderSrcStr, "Resources/Shaders/VertexShader.shader");
	std::cout << VertexShaderSrcStr;

	std::string FragShaderSrcStr;
	ReadShader(FragShaderSrcStr, "Resources/Shaders/FragmentShader.shader");
	std::cout << FragShaderSrcStr;
	
	const char* VertexShaderSrcRaw = VertexShaderSrcStr.c_str();
	unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderSrcRaw, nullptr);
	glCompileShader(VertexShader);

	const char* FragShaderSrcRaw = FragShaderSrcStr.c_str();
	unsigned int FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader,1, &FragShaderSrcRaw, nullptr);
	glCompileShader(FragShader);

	GetShaderCompliationMsg(VertexShader);
	GetShaderCompliationMsg(FragShader);

	unsigned int Program =  glCreateProgram();
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragShader);
	glLinkProgram(Program);
	glUseProgram(Program);
	GetShaderProgramLinkMsg(Program);

	glDeleteShader(VertexShader);
	glDeleteShader(FragShader);

	unsigned int Texture;
	glGenTextures(1, &Texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	int width, height, comp;
	unsigned char* data = stbi_load("Resources/Texture/PlankTexture.jpg", &width, &height, &comp, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	int TextureUniformLoc = glGetUniformLocation(Program, "Texture");
	glUniform1i(TextureUniformLoc, 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5, 0.3, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "hello world!\n";
}