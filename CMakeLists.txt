
cmake_minimum_required(VERSION 3.1)

project(opengl) 

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake") 
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan") 
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake") 
endif() 

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
    PROFILE ${CMAKE_CONNAN_PROFILE}
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

add_subdirectory(3rd_party)
 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_executable(opengl src/main.cpp)

target_link_libraries(opengl glad glfw)

set_target_properties(opengl PROPERTIES
              CXX_STANDARD 17)

install(TARGETS opengl 
  RUNTIME DESTINATION bin
  RESOURCE DESTINATION bin/res 
)



