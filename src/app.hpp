#pragma once

#include <cstdint>
#include <memory>

#include "Iapp.hpp"
#include "device.hpp"
#include "dynamic_renderpass.hpp"
#include "movement_controller.hpp"
#include "sceneV2/scene.hpp"
#include "swapchain.hpp"
#include "circular_queue.hpp"
#include "window.hpp"

namespace TTe {
class App : public IApp {
   public:
    App() {};
    ~App() {};
    // set up the application
    void init(Device* device, SwapChain* swapchain, Window* window);
    void resize(int width, int height);

    // update the application
    void update(float deltaTime, CommandBuffer& cmdBuffer, Window& windowObj);
    void renderFrame(float deltatTime, CommandBuffer& cmdBuffer, uint32_t curentFrameIndex);

   private:
  
    SwapChain* swapchain;
    
    DynamicRenderPass renderPass;
    MovementController movementController;

    
    std::shared_ptr<Scene2> scene2;

    float time = 0.0f;
    uint32_t tick = 0; 
};
}  // namespace TTe