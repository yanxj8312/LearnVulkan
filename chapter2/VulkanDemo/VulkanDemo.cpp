// VulkanDemo.cpp: 定义应用程序的入口点。
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


#include <iostream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <optional>
#include <vector>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerExt(VkInstance instance,const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
	const VkAllocationCallbacks * pAllocator,VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
		auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,"vkCreateDebugUtilsMessengerEXT");
	}


class TrangleApplication
{
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}


private:
	GLFWwindow *window = nullptr;
	VkInstance instance;

	void initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
		window = glfwCreateWindow(WIDTH,HEIGHT,"Vulkan",nullptr,nullptr);
	}

	void initVulkan()
	{
		createInstance();
		setupDebugCallback();
		pickPhysicalDevice();
	}

	//显卡存放在类成员 VkPhysicalDevice句柄当中，当VkInstance销毁时这个对象也会被隐士销毁
	void pickPhysicalDevice()
	{
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		//获取图形卡列表方式
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance,&deviceCount,nullptr);
		if(deviceCount == 0)
		{
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		//分配数组存储physialdevice 句柄
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance,&deviceCount,devices.data());

		for(const auto & device : devices)
		{
			if(isDeviceSuitalbe(device))
			{
				physicalDevice = device;
				break;
			}
		}

		if(physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("failed to find a suitable GPU!");
		}

	}
	//寻找合适的设备
	bool isDeviceSuitalbe(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device,&deviceProperties);
		vkGetPhysicalDeviceFeatures(device,&deviceFeatures);

		return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
			deviceFeatures.geometryShader;
	}



	void mainLoop()
	{
		while(!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
		}
	}

	void createInstance()
	{
		//创建程序信息
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.pApplicationName = "hello trangle";
		appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		//创建接口inxi
		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		//设置平台扩展
		unsigned int glfwExtensionCout = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCout);
		createInfo.enabledExtensionCount = glfwExtensionCout;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		//创建vulkan 实例
		if(vkCreateInstance(&createInfo,nullptr,&instance)!=VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}
	}

	void cleanup()
	{
		vkDestroyInstance(instance,nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
	}


};



int main()
{
	TrangleApplication app;

	try
	{
		app.run();
	} catch(const std::exception &e)
	{
		std::cerr<<e.what()<<std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

	return 0;
}
