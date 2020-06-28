# CMakeList.txt: VulkanDemo 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)


include_directories(../)
include_directories(../3rdpart/include)
include_directories(${VULKAN_INCLUDE})


link_directories(../3rdpart/Bin32)
link_directories(${VULKAN_LIB})

# 将源代码添加到此项目的可执行文件。
add_executable (VulkanDemo "VulkanDemo.cpp" )

# TODO: 如有需要，请添加测试并安装目标。

target_link_libraries(VulkanDemo vulkan-1)

target_link_libraries(VulkanDemo glfw3)

target_link_libraries(VulkanDemo SDL2)

target_link_libraries(VulkanDemo glfw3dll)

