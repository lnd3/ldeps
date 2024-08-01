cmake_minimum_required (VERSION 3.0.2)

if(NOT DEFINED deps_various OR deps_various)
############################ Various ############################
file(GLOB_RECURSE various_inc ${CMAKE_CURRENT_SOURCE_DIR}/various/include/various/*.h)
file(GLOB_RECURSE various_src ${CMAKE_CURRENT_SOURCE_DIR}/various/src/*.*)
add_library(various STATIC ${various_inc} ${various_src})
target_include_directories(various PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/various/include)
set_target_properties(various PROPERTIES FOLDER "Deps/various")

target_compile_definitions(various PUBLIC cxx_std_17)
endif()

if(NOT DEFINED deps_glad OR deps_glad)
############################ GLAD ############################
add_library(glad STATIC 
	${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
	${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
	${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set_target_properties(glad PROPERTIES FOLDER "Deps/glad")

target_compile_definitions(glad PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(glad PRIVATE /W2 /WX)
else()
	target_compile_options(glad PRIVATE -Werror)
endif()
endif()
