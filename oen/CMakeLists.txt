

add_library(oen INTERFACE)

target_link_libraries(oen INTERFACE ogl ogl-loader) 

target_include_directories(oen INTERFACE ./include)

target_compile_features(oen INTERFACE cxx_std_17)

set(shader_files
	res/solid_color.vs
	res/solid_color.fs
)

file(COPY ${shader_files}
	DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/shader)

install(TARGETS oen
  RUNTIME DESTINATION bin
  RESOURCE DESTINATION bin/res
)

