# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

set(VULKAN_INCLUDE "C:\\VulkanSDK\\1.2.141.2\\Include")
set(VULKAN_LIB "C:\\VulkanSDK\\1.2.141.2\\Lib32")
project ("VulkanDemo")

# 包含子项目。
add_subdirectory ("VulkanDemo")
