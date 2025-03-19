//
// Created by School on 2025/3/14.
//

#ifndef CELESTEPET_VK_ENGINE_H
#define CELESTEPET_VK_ENGINE_H

#include <ranges>

#include "vulkan/vk_types.h"
#include "vk_descriptors.h"

#ifdef _WIN32
#include "windows/game_window.h"
#include "windows/data_type.h"
#endif//_WIN32

constexpr unsigned int FRAME_OVERLAP = 2;

namespace Madline {
	struct DeletionQueue {
		// To improve, we could instead store the handles (pointers) to the objects, then delete them
		std::deque<std::function<void()>> deletors;
		
		void pushFunction(std::function<void()>&& function) {
			deletors.push_back(function);
		}
		
		void flush() {
			// reverse iterate the deletion queue to execute all the functions
			for (auto& deletor : std::ranges::reverse_view(deletors)) {
				deletor(); //call functors
			}
	
			deletors.clear();
		}
	};
	
	struct FrameData {
		VkCommandPool commandPool;
		VkCommandBuffer mainCommandBuffer;
		VkSemaphore swapchainSemaphore, renderSemaphore;
		VkFence renderFence;
		DeletionQueue deletionQueue;
	};
	
	class GraphicsEngine {
	private:
		bool isInitialized { false };
		int frameNumber {0};
		
		VkExtent2D windowExtent{ sizeof(VkExtent2D) };
		
		Window* mWindow{ nullptr };
		
		VkInstance instance{};// Vulkan library handle
		VkDebugUtilsMessengerEXT debugMessenger{};// Vulkan debug output handle
		VkPhysicalDevice chosenGpu{};// GPU chosen as the default device
		VkDevice device{}; // Vulkan device for commands
	
		std::array<FrameData, 2> frames;
		FrameData& getCurrentFrame() { return frames[frameNumber % FRAME_OVERLAP]; };
		
		VkQueue graphicsQueue{};
		uint32_t graphicsQueueFamily{};
		
		VkSurfaceKHR surface{};// Vulkan window surface
		VkSwapchainKHR swapchain{};
		VkFormat swapchainImageFormat{};
		VkExtent2D swapchainExtent{};
		VkExtent2D drawExtent{};
	
		std::vector<VkImage> swapchainImages;
		std::vector<VkImageView> swapchainImageViews;
		
		VkDescriptorSet drawImageDescriptors{};
		VkDescriptorSetLayout drawImageDescriptorLayout{};
		
		VkPipeline gradientPipeline{};
		VkPipelineLayout gradientPipelineLayout{};
		
		DeletionQueue mainDeletionQueue;
		
		VmaAllocator allocator{};
		DescriptorAllocator globalDescriptorAllocator{};
		
		AllocatedImage drawImage{};
		
		void initVulkan(const Madline::Window& window);
		void initSwapchain();
		void initCommands();
		void initSyncStructures();
		void initDescriptors();
		void initPipelines();
		void initBackgroundPipelines();
		
		void createSwapchain(uint32_t width, uint32_t height);
		void destroySwapchain();
		
		void drawBackground(VkCommandBuffer cmd) const;
	public:
		//initializes everything in the engine
		void init(Madline::Window&pWindow);
		
		//shuts down the engine
		void cleanup();

		//draw loop
		void draw();
		
		GraphicsEngine() = default;
		
		~GraphicsEngine();
	};
}

namespace GEngineTools {
	void exitOnError(std::string msg);
}

#endif//CELESTEPET_VK_ENGINE_H
