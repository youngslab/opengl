
cmake_minimum_required(VERSION 3.1)

project(ogl)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
    PROFILE ${CMAKE_CONNAN_PROFILE}
		# BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(3rd_party)
add_subdirectory(ogl)
add_subdirectory(example)
add_subdirectory(ren)





