
add_executable(simple_texture_example 
	simple_texture_example.cpp
	)

target_link_libraries(simple_texture_example ogl glfw ogl-loader)

set(RESOURCE_FILES
	./simple_texture.fs
	./simple_texture.vs
  ./container.jpg	
)

file(COPY ${RESOURCE_FILES} 
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


