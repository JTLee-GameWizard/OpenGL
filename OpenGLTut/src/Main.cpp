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

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5, 0.3, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "hello world!\n";
}