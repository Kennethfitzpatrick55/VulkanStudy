#pragma once
#include <GLFW/glfw3.h>
#include <gsl/gsl>
#include <glm/vec2.hpp>


struct GlFWmonitor;
struct GLFWwindow;

namespace VulkanEngine
{
    gsl::span<GLFWmonitor*> GetMonitors();
    glm::ivec2 GetMonitorPosition(gsl::not_null<GLFWmonitor*> monitor);
    glm::ivec2 GetMonitorWorkAreaSize(gsl::not_null<GLFWmonitor*> monitor);
    void MoveWindowToMonitor(
    gsl::not_null<GLFWwindow*> window, gsl::not_null<GLFWmonitor*> monitor);
    }
