#include <GLFW/glfw3.h>
#include<glfw_Initialization.h>

std::int32_t main(std::int32_t argc, gsl::zstring* argv) {
  const VulkanEngine::GLfwInitialization _glfw;

  gsl::not_null Window = glfwCreateWindow(800, 600, "Vulkan Engine", nullptr, nullptr);

  gsl::final_action _Cleanup_Window([Window] {
    glfwDestroyWindow(Window);
  });

  std::int32_t monitor_count = 0;
  GLFWmonitor** monitor_pointers = glfwGetMonitors(&monitor_count);
  gsl::span<GLFWmonitor*> monitors(monitor_pointers, monitor_count);

  glm::ivec2 monitor_position;
  glfwGetMonitorPos(monitors[2], &monitor_position.x, &monitor_position.y);


  glm::ivec2 Window_Size;
  glfwGetWindowSize(Window, &Window_Size.x, &Window_Size.y);

  glm::ivec2 monitor_size;
  glfwGetMonitorWorkarea(monitors[2],nullptr,nullptr, &monitor_size.x, &monitor_size.y);

  glm::ivec2 window_new_postion = monitor_position + (monitor_size / 2) - (Window_Size / 2);
  glfwSetWindowPos(Window, window_new_postion.x, window_new_postion.y);

  while (!glfwWindowShouldClose(Window)) {
    glfwPollEvents();
  }
    
    return EXIT_SUCCESS;
}
