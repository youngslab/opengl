

# simple texture
add_executable(ogl-example-texture
	ogl-example-texture.cpp
)

target_link_libraries(ogl-example-texture ogl glfw ogl-loader)

set(shader_files
	./simple_texture.fs
	./simple_texture.vs
)
set(image_files
  ../res/image/container.jpg
  ../res/image/awesomeface.png
)

file(COPY ${shader_files}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/shader)

file(COPY ${image_files}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/image)

