cmake_minimum_required (VERSION 3.0.2)

project(ldeps)

set(TEST_VULKAN False)

# deps thirdparty
set(deps_jsonxx True)
set(deps_curl True)
set(deps_mongoose True)

# deps thirdparty mods
set(deps_glfw True)
set(deps_imgui True)
set(deps_implot True)
set(deps_pugixml True)
set(deps_openfbx True)
set(deps_ufbx True)
set(deps_bc7enc True)

# deps in repo src
set(deps_glad True)
set(deps_various True)

add_subdirectory(thirdparty)
add_subdirectory(thirdparty_mods)
add_subdirectory(src)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/thirdparty/bs/cmake)

get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
endif()

