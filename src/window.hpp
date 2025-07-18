#pragma once

#include <glm/glm.hpp>
#include <string>
#include <chrono>

#include "volk.h"
#include "VkBootstrap.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace TTe {
class Window {
   public:
    Window(unsigned int width, unsigned int height, std::string name);
    ~Window();

    /**
     * Only one window should be created for this engine.
     */
    // desable copy
    Window(Window const &) = delete;
    Window &operator=(Window const &) = delete;
    // desable move
    Window(Window &&) = delete;
    Window &operator=(Window &&) = delete;

    operator GLFWwindow *() const { return window; }

    // getter
    VkSurfaceKHR &getSurface(const vkb::Instance &vkInstance);
    const VkExtent2D &getExtent() const { return size; }
    const VkExtent2D &getExtentGLFW();
    
    const GLFWwindow *getGLFWwindow() const { return window; }
    bool wasWindowResized() const { return framebufferResized; }
    bool shouldClose() const { return glfwWindowShouldClose(window); }

    // setter
    void resetWindowResizedFlag() { framebufferResized = false; }

    glm::vec3 mouseMove{0};
    bool moveCam = false;
    double lastX{0}, lastY{0};
    std::chrono::time_point<std::chrono::system_clock> mouseLastMoved;


   private:
    static void framebufferResizeCallback(GLFWwindow *window, int width, int height);


    VkExtent2D size = {0, 0};

    bool framebufferResized = false;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    GLFWwindow *window = nullptr;
};
}  // namespace TTe