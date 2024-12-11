#include <glfw_initialization.h>
#include <GLFW/glfw3.h>


namespace VulkanEngine
{
  GLfwInitialization::GLfwInitialization()
  {
    if (glfwInit() != GLFW_TRUE) {
       exit(EXIT_FAILURE);
  }
  }
  GLfwInitialization::~GLfwInitialization()
  {
    glfwTerminate();
  }
}
//namespace VulkanEngine
