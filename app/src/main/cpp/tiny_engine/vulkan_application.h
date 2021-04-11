#ifndef TINY_ENGINE_VULKAN_APPLICATION_H
#define TINY_ENGINE_VULKAN_APPLICATION_H

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

namespace tiny_engine {

struct QueueFamilyIndices {
    int32_t graphics_family = -1;
    int32_t present_family = -1;

    virtual bool IsComplete() {
        return graphics_family >= 0 && present_family >= 0;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

class VulkanApplication {
public:
    virtual void Init();

    virtual void Draw();

    virtual void Cleanup();

protected:
    virtual void CreateInstance();

    virtual void CreateDebugMessenger();

    virtual void CreateSurface();

    virtual void CreateDevice();

    virtual void CreateSwapchain();

    virtual void CreateSwapchainImageViews();

    virtual void CreateRenderPass();

    virtual void CreateGraphicsPipeline();

    virtual void CreateShaderModules();

    virtual void CreateFramebuffers();

    virtual void CreateCommandPool();

    virtual void CreateCommandBuffers();

    virtual void CreateSyncObjects();

    virtual void CreateVertexBuffer();

    virtual void CreateIndexBuffer();

    virtual void CreateDescriptorSetLayout();

    virtual void CreateUniformBuffers();

    virtual void CreateDescriptorPool();

    virtual void CreateDescriptorSets();

    virtual void CreateTextureImage();

    virtual void CreateTextureImageView();

    virtual void CreateTextureSampler();

    virtual void CreateDepthResources();

    virtual void DestroyShaderModules();

    virtual void DestroySwapchainImageViews();

    virtual void DestroyDebugMessenger();

protected:
    virtual VkPhysicalDevice PickPhysicalDevice(VkInstance instance,
                                                const std::vector<const char *> &extensions,
                                                VkSurfaceKHR surface);

    virtual QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device,
                                                 VkSurfaceKHR surface);

    virtual SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device,
                                                          VkSurfaceKHR surface);

    virtual bool CheckDeviceExtensionSupport(VkPhysicalDevice device,
                                             const std::vector<const char *> &extensions);

    virtual VkSurfaceFormatKHR
    ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &available_formats);

    virtual VkPresentModeKHR
    ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> &available_present_modes);

    virtual VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    virtual VkImageView CreateImageView(VkDevice device, VkImage image, VkFormat format,
                                        VkImageAspectFlags aspect_flags);

    virtual VkFormat FindDepthFormat(VkPhysicalDevice physical_device);

    virtual VkFormat FindSupportedFormat(VkPhysicalDevice physical_device,
                                         const std::vector<VkFormat> &candidates,
                                         VkImageTiling tiling,
                                         VkFormatFeatureFlags features);

    virtual VkShaderModule CreateShaderModule(VkDevice device, const std::vector<char> &code);

protected:
    std::string application_name_;
    std::vector<const char *> extensions_;
    std::vector<const char *> layers_;
    std::vector<const char *> device_extensions_ = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    std::vector<char> vert_shader_code_;
    std::vector<char> frag_shader_code_;
    std::vector<VkVertexInputBindingDescription> binding_descriptions_;
    std::vector<VkVertexInputAttributeDescription> attribute_descriptions_;

    VkInstance instance_ = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debug_messenger_ = VK_NULL_HANDLE;

    void *native_window_ = nullptr;
    VkSurfaceKHR surface_ = VK_NULL_HANDLE;

    VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkQueue graphics_queue_ = VK_NULL_HANDLE;
    VkQueue present_queue_ = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain_ = VK_NULL_HANDLE;
    std::vector<VkImage> swapchain_images_;
    VkFormat swapchain_image_format_;
    VkExtent2D swapchain_extent_;
    std::vector<VkImageView> swapchain_image_views_;

    VkRenderPass render_pass_ = VK_NULL_HANDLE;
    VkShaderModule vert_shader_module_ = VK_NULL_HANDLE;
    VkShaderModule frag_shader_module_ = VK_NULL_HANDLE;

    VkDescriptorSetLayout descriptor_set_layout_ = VK_NULL_HANDLE;
    VkPipelineLayout pipeline_layout_ = VK_NULL_HANDLE;
    VkPipeline graphics_pipeline_ = VK_NULL_HANDLE;

    VkCommandPool command_pool_ = VK_NULL_HANDLE;

    VkImage depth_image_;
    VkDeviceMemory depth_image_memory_;
    VkImageView depth_image_view_;
    std::vector<VkFramebuffer> framebuffers_;
};

} //namespace tiny_engine

#endif //TINY_ENGINE_VULKAN_APPLICATION_H
