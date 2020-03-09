

add_library(oen INTERFACE)

target_link_libraries(oen INTERFACE ogl) 

target_include_directories(oen INTERFACE ./include)

target_compile_features(oen INTERFACE cxx_std_17)

install(TARGETS oen
  RUNTIME DESTINATION bin
  RESOURCE DESTINATION bin/res
)

