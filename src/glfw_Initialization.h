#pragma once
namespace VulkanEngine {

struct GLfwInitialization
{
 public:
  GLfwInitialization();
  ~GLfwInitialization();

  GLfwInitialization(const GLfwInitialization&) = delete;

  GLfwInitialization& operator=(const GLfwInitialization&) = delete;
};

}  // namespace VulkanEngine
