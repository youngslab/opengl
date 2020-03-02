
find_package(Assimp REQUIRED)
find_package(soil2 REQUIRED)
find_package(fmt REQUIRED)

add_library(ogl-loader STATIC
	src/loader.cpp)

target_link_libraries(ogl-loader PUBLIC glad Assimp::Assimp 
		soil2::soil2
			fmt::fmt)

target_include_directories(ogl-loader PUBLIC ./include)

target_compile_features(ogl-loader PUBLIC cxx_std_17)

add_subdirectory(example)
