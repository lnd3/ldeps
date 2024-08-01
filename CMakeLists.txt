cmake_minimum_required (VERSION 3.0.2)

add_subdirectory(thirdparty)
add_subdirectory(thirdparty_mods)
add_subdirectory(src)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/deps/bs/cmake)

