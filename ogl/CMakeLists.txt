

find_package(glm REQUIRED)
find_package(fmt REQUIRED)

add_library(ogl STATIC
	src/shader.cpp
	src/texture.cpp
	src/resource.cpp
	src/indexbuffer.cpp
	src/vertexattribute.cpp
	src/vertexbuffer.cpp
	src/vertexarray.cpp
	src/program.cpp
	src/framebuffer.cpp)

target_link_libraries(ogl PUBLIC glad glm::glm
			fmt::fmt)

target_include_directories(ogl PUBLIC ./include)

target_compile_features(ogl PUBLIC cxx_std_17)
#set_target_properties(ogl PUBLIC PROPERTIES
              #CXX_STANDARD 17)

install(TARGETS ogl
  RUNTIME DESTINATION bin
  RESOURCE DESTINATION bin/res
)
