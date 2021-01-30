#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
int main()
{
	glfwInit();
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));
	
	std::cout << "hello world!\n";
}