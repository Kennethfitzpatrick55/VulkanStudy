#include <GLFW/glfw3.h>
#include<glfw_Initialization.h>
#include<glfw_monitor.h>

std::int32_t main(std::int32_t argc, gsl::zstring* argv) {
  const VulkanEngine::GLfwInitialization _glfw;

  gsl::not_null Window = glfwCreateWindow(800, 600, "Vulkan Engine", nullptr, nullptr);

  gsl::final_action _Cleanup_Window([Window] {
    glfwDestroyWindow(Window);
  });

  
  gsl::span<GLFWmonitor*> monitors = VulkanEngine::GetMonitors();
  if (monitors.size() > 1)
  {
    VulkanEngine::MoveWindowToMonitor(Window, monitors[1]);
  }

 
  while (!glfwWindowShouldClose(Window)) {
    glfwPollEvents();
  }
    
    return EXIT_SUCCESS;
}
