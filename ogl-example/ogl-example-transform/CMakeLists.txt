

# simple texture
add_executable(ogl-example-transform
	ogl-example-transform.cpp
)

target_link_libraries(ogl-example-transform ogl glfw ogl-loader)

set(shader_files
	./transform.fs
	./transform.vs
)
set(image_files
  ../res/image/container.jpg
  ../res/image/awesomeface.png
)

file(COPY ${shader_files}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/shader)

file(COPY ${image_files}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/image)

