if(NOT DEFINED deps_glfw OR deps_glfw)
############################ GLFW ############################
set(BUILD_SHARED_LIBS Off)
set(GLFW_BUILD_EXAMPLES Off)
set(GLFW_BUILD_TESTS Off)
set(GLFW_BUILD_DOCS Off)
set(GLFW_INSTALL Off)
add_subdirectory(glfw)
set_target_properties(glfw PROPERTIES FOLDER "Deps/thirdparty_mods/glfw")
set_target_properties(update_mappings PROPERTIES FOLDER "Deps/thirdparty_mods/glfw")
endif()

if(NOT DEFINED deps_imgui OR deps_imgui)
############################ imgui ############################
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/imgui_impl_glfw.h ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/imgui_impl_glfw.h COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/imgui_impl_glfw.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/imgui_impl_glfw.cpp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/imgui_impl_opengl3.h ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/imgui_impl_opengl3.h COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/imgui_impl_opengl3.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/imgui_impl_opengl3.cpp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/imgui_impl_opengl3_loader.h ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/imgui_impl_opengl3_loader.h COPYONLY)

set(imgui_includes)
find_package(Vulkan QUIET)
if(TARGET Vulkan::Vulkan)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/imgui_impl_vulkan.h ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/imgui_impl_vulkan.h COPYONLY)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/backends/imgui_impl_vulkan.cpp ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui/imgui_impl_vulkan.cpp COPYONLY)
	set(APPEND imgui_includes ${Vulkan_INCLUDE_DIRS})
endif()

file(GLOB im_inc imgui/imgui/im*.h)
file(GLOB im_src imgui/imgui/im*.cpp)
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui PREFIX imgui FILES ${im_inc})
add_library(imgui STATIC ${im_src} ${im_inc})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui ${imgui_includes})
target_link_libraries(imgui PRIVATE glfw)

if(TARGET Vulkan::Vulkan)
	target_include_directories(imgui PRIVATE ${imgui_includes})
	target_link_libraries(imgui PRIVATE Vulkan::Vulkan)
endif()

set_target_properties(imgui PROPERTIES FOLDER "Deps/thirdparty_mods/imgui")

if(WIN32)
	add_executable(example_glfw_opengl3 imgui/imgui/examples/example_glfw_opengl3/main.cpp)
	target_link_libraries(example_glfw_opengl3 PRIVATE imgui glfw opengl32.lib glu32.lib winmm.lib)
	set_target_properties(example_glfw_opengl3 PROPERTIES FOLDER "Deps/thirdparty_mods/imgui")
endif()

endif()

if(NOT DEFINED deps_implot OR deps_implot)
############################ implot ############################
set(implot_includes
	${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/implot.h
	${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/implot_internal.h
)
set(implot_source
	${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/implot.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/implot_items.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/implot_demo.cpp
)
add_library(implot STATIC ${implot_includes} ${implot_source})
target_include_directories(implot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/implot)
target_link_libraries(implot PRIVATE imgui)
set_target_properties(implot PROPERTIES FOLDER "Deps/thirdparty_mods/implot")

if(WIN32)
	add_executable(implot_demo ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/implot_demo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/main.cpp)
	target_link_libraries(implot_demo PRIVATE imgui implot glfw opengl32.lib glu32.lib winmm.lib)
	set_target_properties(implot_demo PROPERTIES FOLDER "Deps/thirdparty_mods/implot")
endif()

endif()

if(NOT DEFINED deps_pugixml OR deps_pugixml)
############################ pugixml ############################
file(GLOB px_inc ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/pugixml/src/*.hpp)
file(GLOB px_src ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/pugixml/src/*.cpp)
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/pugixml/src PREFIX pugixml FILES ${px_inc})

add_library(pugixml STATIC ${px_inc} ${px_src})
target_include_directories(pugixml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pugixml)
target_link_libraries(pugixml)
set_target_properties(pugixml PROPERTIES FOLDER "Deps/thirdparty_mods/pugixml")
if(MSVC)
	target_compile_options(pugixml PRIVATE /W1 /WX)
else()
	target_compile_options(pugixml PRIVATE -Werror)
endif()
endif()

if(NOT DEFINED deps_openfbx OR deps_openfbx)
############################ openfbx ############################
file(GLOB of_inc ${CMAKE_CURRENT_SOURCE_DIR}/openfbx/openfbx/src/*.h)
file(GLOB of_src ${CMAKE_CURRENT_SOURCE_DIR}/openfbx/openfbx/src/*.c*)
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/openfbx/openfbx/src PREFIX openfbx FILES ${of_inc})
add_library(openfbx STATIC ${of_inc} ${of_src})
target_include_directories(openfbx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openfbx)
target_link_libraries(openfbx)
set_target_properties(openfbx PROPERTIES FOLDER "Deps/thirdparty_mods/openfbx")

target_compile_definitions(openfbx PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(openfbx PRIVATE /W1 /WX)
else()
	target_compile_options(openfbx PRIVATE -Werror)
endif()
endif()

if(NOT DEFINED deps_ufbx OR deps_ufbx)
############################ ufbx ############################
add_library(ufbx STATIC ${CMAKE_CURRENT_SOURCE_DIR}/ufbx/ufbx/ufbx.h ${CMAKE_CURRENT_SOURCE_DIR}/ufbx/ufbx/ufbx.c)
target_include_directories(ufbx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ufbx)
target_link_libraries(ufbx)
set_target_properties(ufbx PROPERTIES FOLDER "Deps/thirdparty_mods/ufbx")

target_compile_definitions(ufbx PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(ufbx PRIVATE /W2 /WX)
else()
	target_compile_options(ufbx PRIVATE -Werror)
endif()
endif()

if(NOT DEFINED deps_bc7enc OR deps_bc7enc)
############################ bc7enc ############################
file(GLOB_RECURSE bc7enc_inc ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc/bc7enc/*.h)
file(GLOB_RECURSE bc7enc_src ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc/bc7enc/*.c*)
list(REMOVE_ITEM bc7enc_src ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc/bc7enc/test.cpp)

add_library(bc7enc STATIC ${bc7enc_inc} ${bc7enc_src})
target_include_directories(bc7enc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc)
set_target_properties(bc7enc PROPERTIES FOLDER "Deps/thirdparty_mods/bc7enc")

target_compile_definitions(bc7enc PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(bc7enc PRIVATE /W1)
else()
	target_compile_options(bc7enc PRIVATE -Werror)
endif()
endif()

if(NOT DEFINED deps_cryptopp OR deps_cryptopp)
############################ bc7enc ############################
file(GLOB cryptopp_inc ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/cryptopp/*.h)
file(GLOB cryptopp_src ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/cryptopp/*.c*)
list(REMOVE_ITEM cryptopp_src ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc/bc7enc/blake2b_simd.cpp)

add_library(cryptopp STATIC ${cryptopp_inc} ${cryptopp_src})
target_include_directories(cryptopp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp)
set_target_properties(cryptopp PROPERTIES FOLDER "Deps/thirdparty_mods/cryptopp")

target_compile_definitions(cryptopp PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(cryptopp PRIVATE /W1)
else()
	target_compile_options(cryptopp PRIVATE -Werror)
endif()
endif()