

add_library(ren INTERFACE)

target_link_libraries(ren INTERFACE ogl) 

target_include_directories(ren INTERFACE ./include)

target_compile_features(ren INTERFACE cxx_std_17)


install(TARGETS ren
  RUNTIME DESTINATION bin
  RESOURCE DESTINATION bin/res
)

add_subdirectory(example)
