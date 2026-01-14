cmake_minimum_required(VERSION 3.22)

# Set your project name
project(OtusBasicHomework06 VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not specified (options: Debug, Release, RelWithDebInfo, MinSizeRel)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Microsoft Visual C++ specific flags
    add_compile_options(/W4)
    add_compile_definitions(NOMINMAX)
else()
    # GCC/Clang specific flags
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Add your executable (replace main.cpp with your source files)
add_executable(${PROJECT_NAME} 
    main.cpp
)

# Example: Add include directories if needed
# target_include_directories(${PROJECT_NAME} PRIVATE 
#     include
# )

# Example: Link libraries if needed
# find_package(SomeLibrary REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE SomeLibrary::SomeLibrary)

# Example: Add a library if you have multiple components
# add_library(your_library 
#     src/your_library.cpp
# )
# target_link_libraries(${PROJECT_NAME} PRIVATE your_library)
