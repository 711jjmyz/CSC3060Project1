cmake_minimum_required(VERSION 3.30)
project(data_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Library target
add_library(data_lab src/data_lab.cpp)
target_include_directories(data_lab PUBLIC include)

# Test target
enable_testing()
add_executable(test_data_lab test/test_data_lab.cpp)
target_link_libraries(test_data_lab data_lab gtest_main)
add_test(NAME DataLabTests COMMAND test_data_lab)



# ========================================================
#  Mystery Test Configuration (Added by User)
# ========================================================

# 1. 生成测试可执行文件
# 关键点：必须同时编译 "测试代码" 和 "你的实现代码(src/data_lab.cpp)"
# 否则编译器会报错：Undefined reference to 'divide'
add_executable(test_mystery_minus_one 
    test/test_mystery_minus_one.cpp 
    src/data_lab.cpp
)

# 2. 指定头文件路径
# 让编译器知道去 include 文件夹里找 data_lab.hpp
target_include_directories(test_mystery_minus_one PRIVATE include)

# 3. (可选) 开启编译器警告，这对 Debug很有帮助
target_compile_options(test_mystery_minus_one PRIVATE -Wall -Wextra)

# 4. (可选) 注册到 CTest
# 这样你也可以通过输入 'ctest' 来运行这个测试
add_test(NAME MysteryMinusOne COMMAND test_mystery_minus_one)




# ==========================================
# Power of 2 Advanced Test Configuration
# ==========================================

# 直接把 src/data_lab.cpp 加到可执行文件中，跳过链接步骤
add_executable(test_power_of_2 test/test_power_of_2.cpp src/data_lab.cpp)

# 设置头文件路径
target_include_directories(test_power_of_2 PRIVATE include)

# 注册到 CTest
add_test(NAME PowerOf2Test COMMAND test_power_of_2)