#pragma once


#include <string>
#include "commandBuffer/command_buffer.hpp"
#include "shader/pipeline.hpp"
#include "shader/shader.hpp"
namespace TTe {
struct GraphicPipelineCreateInfo{
    std::string vexterShaderFile;
    std::string fragmentShaderFile;
    std::string tesselationControlShaderFile;
    std::string tesselationEvaluationShaderFile;
    std::string geometryShaderFile;
};

class GraphicPipeline : public Pipeline {

   public:
    GraphicPipeline(){};
    GraphicPipeline(Device *device, GraphicPipelineCreateInfo& pipelineCreateInfo);
    ~GraphicPipeline();


    // Move constructor
    GraphicPipeline(GraphicPipeline &&other);
    GraphicPipeline &operator=(GraphicPipeline &&other);


    VkPipelineLayout getPipelineLayout(){return vk_pipelineLayout;};
    std::shared_ptr<DescriptorSetLayout> getDescriptorSetLayout(uint32_t id){return pipelineDescriptorsSetsLayoutList[id];}
    

    void bindPipeline(const CommandBuffer &cmdBuffer);
    void reloadShader(VkShaderStageFlagBits shaderStageToReload);
   private:

    void createShaders(GraphicPipelineCreateInfo& pipelineCreateInfo);

    Shader  createFragmentShader(GraphicPipelineCreateInfo& pipelineCreateInfo);
    Shader  createVertexShader(GraphicPipelineCreateInfo& pipelineCreateInfo, VkShaderStageFlagBits nextStageFlag);
    Shader  createTesselationControlShader(GraphicPipelineCreateInfo& pipelineCreateInfo, VkShaderStageFlagBits nextStageFlag);
    Shader  createTesselationEvaluationShader(GraphicPipelineCreateInfo& pipelineCreateInfo, VkShaderStageFlagBits nextStageFlag);
    Shader  createGeometryShader(GraphicPipelineCreateInfo& pipelineCreateInfo, VkShaderStageFlagBits nextStageFlag);

    void setPipelineStage(GraphicPipelineCreateInfo& pipelineCreateInfo);
    void createPipelineLayout(GraphicPipelineCreateInfo& pipelineCreateInfo);
    void createVertexShaderInfo();

    void setVextexInfo(VkCommandBuffer cmdBuffer);

    void setRasterizerInfo(VkCommandBuffer cmdBuffer);

    void setFragmentInfo(VkCommandBuffer cmdBuffer);

    VkVertexInputBindingDescription2EXT vertexInputBinding = {};
    std::vector<VkVertexInputAttributeDescription2EXT> vertexAttributes;

    std::map<VkShaderStageFlagBits, Shader> shadersMap;
    
    VkShaderStageFlags pipelineStageFlags = 0;
    std::unordered_map<std::vector<uint32_t>, std::shared_ptr<DescriptorSetLayout>> pipelineDescriptorsSetsLayout;
    std::map<uint32_t ,std::shared_ptr<DescriptorSetLayout>> pipelineDescriptorsSetsLayoutList;

    

    Device *device = nullptr;
};

}  // namespace vk_stage