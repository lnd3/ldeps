
# Glob Darknet headers and sources
set(USE_CUDA OFF CACHE BOOL "Disable CUDA for CPU-only build")

file(GLOB darknet_inc ${CMAKE_CURRENT_SOURCE_DIR}/darknet/include/*.h)
file(GLOB darknet_src ${CMAKE_CURRENT_SOURCE_DIR}/darknet/src/*.*)
list(FILTER darknet_src EXCLUDE REGEX "compare\\.c$")
if(NOT USE_CUDA)
	list(FILTER darknet_src EXCLUDE REGEX "\\.cu$")
endif()
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/darknet/include PREFIX darknet FILES ${darknet_inc})

add_library(darknet STATIC ${darknet_inc} ${darknet_src})
target_include_directories(darknet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/darknet/include)
target_link_libraries(darknet PUBLIC pthreads)

# Add examples
if(deps_darknet_examples)
add_executable(darknet_example_darknet ${CMAKE_CURRENT_SOURCE_DIR}/darknet/examples/darknet.c)
target_link_libraries(darknet_example_darknet PRIVATE pthreads darknet)
add_executable(darknet_example_dice ${CMAKE_CURRENT_SOURCE_DIR}/darknet/examples/dice.c)
target_link_libraries(darknet_example_dice PRIVATE pthreads darknet)
add_executable(darknet_example_detector ${CMAKE_CURRENT_SOURCE_DIR}/darknet/examples/detector.c)
target_link_libraries(darknet_example_detector PRIVATE pthreads darknet)

set_target_properties(darknet_example_darknet PROPERTIES FOLDER "Deps/thirdparty/darknet/examples")
set_target_properties(darknet_example_dice PROPERTIES FOLDER "Deps/thirdparty/darknet/examples")
set_target_properties(darknet_example_detector PROPERTIES FOLDER "Deps/thirdparty/darknet/examples")
endif()

set_target_properties(darknet PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
if(MSVC)
	target_compile_options(darknet PRIVATE /W0)
else()
	target_compile_options(darknet PRIVATE -w)
endif()

