
cmake_minimum_required(VERSION 3.1)

project(ogl)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

set(CMAKE_CONAN_PROFILE "default" CACHE STRING "conan profile")

conan_cmake_run(CONANFILE conanfile.txt
    PROFILE ${CMAKE_CONAN_PROFILE}
		# BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



add_subdirectory(3rd_party)
add_subdirectory(ogl)
add_subdirectory(ogl-loader)
add_subdirectory(oen)
# add_subdirectory(oen-loader)
if(${EXAMPLE})
  add_subdirectory(ogl-example)
  add_subdirectory(oen-example)
endif()


