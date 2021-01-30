#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
const int windowWidth = 1280;
const int windowHeight = 720;
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
		-0.5f, -0.5f, 0.f,
		0.5f,  -0.5f, 0.f,
		0.f,    0.5f,  0.f
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5, 0.3, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "hello world!\n";
}