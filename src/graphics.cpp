#include <precomp.h>
#include <graphics.h>
#include <GLFW/glfw3.h>

namespace veng {

Graphics::Graphics(gsl::not_null<Window*> window) : window_(window) {
  InitializeVulkan();
}

Graphics::~Graphics() {
  if (instance_ != nullptr) {
    vkDestroyInstance(instance_, nullptr);
  }
}

void Graphics::InitializeVulkan() {
  CreateInstance();
}

void Graphics::CreateInstance() {
  gsl::span<gsl::czstring> suggested_extensions = GetSuggestedInstanceExtensions();

  if (!AreAllExtensionsSupported(suggested_extensions)) {
    std::exit(EXIT_FAILURE);
  }

  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext = nullptr;  // no extenstions (custom)
  app_info.pApplicationName = "Udemy Course";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "VEng";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instance_creation_info = {};
  instance_creation_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_creation_info.pNext = nullptr;
  instance_creation_info.pApplicationInfo = &app_info;
  instance_creation_info.enabledExtensionCount = suggested_extensions.size();
  instance_creation_info.ppEnabledExtensionNames = suggested_extensions.data();
  instance_creation_info.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&instance_creation_info, nullptr, &instance_);
  if (result != VK_SUCCESS) {
    std::exit(EXIT_FAILURE);
  }
}

gsl::span<gsl::czstring> Graphics::GetSuggestedInstanceExtensions() {
  std::uint32_t glfw_extension_count = 0;
  gsl::czstring* glfw_extensions;
  glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
  return {glfw_extensions, glfw_extension_count};
}

std::vector<VkExtensionProperties> Graphics::GetSupportedInstanceExtensions() {
  std::uint32_t count;
  vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);

  if (count == 0) {
    return {};
  }

  std::vector<VkExtensionProperties> properties(count);
  vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());
  return properties;
}

bool ExtensionMatchesName(gsl::czstring name, const VkExtensionProperties& properties) {
  return veng::streq(properties.extensionName, name);
}

bool IsExtensionSupported(gsl::span<VkExtensionProperties> extensions, gsl::czstring name) {
  return std::any_of(
      extensions.begin(), extensions.end(), std::bind_front(ExtensionMatchesName, name));
}

bool Graphics::AreAllExtensionsSupported(gsl::span<gsl::czstring> extensions) {
  std::vector<VkExtensionProperties> supported_extensions = GetSupportedInstanceExtensions();

  return std::all_of(
      extensions.begin(), extensions.end(),
      std::bind_front(IsExtensionSupported, supported_extensions));
}

}  // namespace veng
