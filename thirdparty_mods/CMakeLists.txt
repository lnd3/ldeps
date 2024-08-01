cmake_minimum_required (VERSION 3.0.2)

############################ External Libs ############################

if(NOT DEFINED TP_jsonxx OR TP_jsonxx)
############################ jsonxx ############################
file(GLOB_RECURSE jsonxx_inc ${CMAKE_CURRENT_SOURCE_DIR}/jsonxx/jsonxx/jsonxx.h)
file(GLOB_RECURSE jsonxx_src ${CMAKE_CURRENT_SOURCE_DIR}/jsonxx/jsonxx/jsonxx.cc)

add_library(jsonxx STATIC ${jsonxx_inc} ${jsonxx_src})
target_include_directories(jsonxx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/jsonxx)
set_target_properties(jsonxx PROPERTIES FOLDER "Deps/jsonxx")

target_compile_definitions(jsonxx PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(jsonxx PRIVATE /W1)
else()
	target_compile_options(jsonxx PRIVATE -Werror)
endif()
endif()


if(NOT DEFINED TP_bc7enc OR TP_bc7enc)
############################ bc7enc ############################
file(GLOB_RECURSE bc7enc_inc ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc/bc7enc/*.h)
file(GLOB_RECURSE bc7enc_src ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc/bc7enc/*.c*)
list(REMOVE_ITEM bc7enc_src ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc/bc7enc/test.cpp)

add_library(bc7enc STATIC ${bc7enc_inc} ${bc7enc_src})
target_include_directories(bc7enc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bc7enc)
set_target_properties(bc7enc PROPERTIES FOLDER "Deps/bc7enc")

target_compile_definitions(bc7enc PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(bc7enc PRIVATE /W1)
else()
	target_compile_options(bc7enc PRIVATE -Werror)
endif()
endif()

if(NOT DEFINED TP_various OR TP_various)
############################ Various ############################
file(GLOB_RECURSE various_inc ${CMAKE_CURRENT_SOURCE_DIR}/various/include/various/*.h)
file(GLOB_RECURSE various_src ${CMAKE_CURRENT_SOURCE_DIR}/various/src/*.*)
add_library(various STATIC ${various_inc} ${various_src})
target_include_directories(various PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/various/include)
set_target_properties(various PROPERTIES FOLDER "Deps/various")

target_compile_definitions(various PUBLIC cxx_std_17)
endif()

if(NOT DEFINED TP_glfw OR TP_glfw)
############################ GLFW ############################
set(BUILD_SHARED_LIBS Off)
set(GLFW_BUILD_EXAMPLES Off)
set(GLFW_BUILD_TESTS Off)
set(GLFW_BUILD_DOCS Off)
set(GLFW_INSTALL Off)
add_subdirectory(glfw)
set_target_properties(glfw PROPERTIES FOLDER "Deps/glfw")
set_target_properties(update_mappings PROPERTIES FOLDER "Deps/glfw")
endif()

if(NOT DEFINED TP_glad OR TP_glad)
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

if(NOT DEFINED TP_curl OR TP_curl)
############################ CURL ############################
set(BUILD_SHARED_LIBS False)
set(BUILD_STATIC_LIBS True)
set(BUILD_TESTING False)
#set(CURL_CA_FALLBACK On)
set(CURL_ENABLE_SSL True)
set(CURL_USE_SCHANNEL True)
set(CURL_WINDOWS_SSPI True)
#set(ENABLE_CURL_DEBUG On)
#set(ENABLE_DEBUG On)
#set(ENABLE_UNIX_SOCKETS On)
set(ENABLE_WEBSOCKETS True)
set(USE_WIN32_LDAP True)
add_subdirectory(curl)
set_target_properties(curl PROPERTIES FOLDER "Deps/curl")
set_target_properties(curl_uninstall PROPERTIES FOLDER "Deps/curl")
set_target_properties(libcurl_static PROPERTIES FOLDER "Deps/curl")
set_target_properties(libcurl_object PROPERTIES FOLDER "Deps/curl")
set_target_properties(curltool PROPERTIES FOLDER "Deps/curl")
target_compile_definitions(libcurl_object PUBLIC CURL_ENABLE_SSL USE_WINDOWS_SSPI USE_SCHANNEL)
endif()

if(NOT DEFINED TP_mongoose OR TP_mongoose)
############################ Mongoose ############################
add_library(mongoose STATIC mongoose/mongoose/mongoose.h mongoose/mongoose/mongoose.c)
target_include_directories(mongoose PUBLIC mongoose)
set_target_properties(mongoose PROPERTIES FOLDER "Deps/mongoose")

target_compile_definitions(mongoose PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(mongoose PRIVATE /W0)
else()
	target_compile_options(mongoose PRIVATE -Werror)
endif()
endif()

if(NOT DEFINED TP_imgui OR TP_imgui)
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

set_target_properties(imgui PROPERTIES FOLDER "Deps/imgui")
add_executable(example_glfw_opengl3 imgui/imgui/examples/example_glfw_opengl3/main.cpp)
target_link_libraries(example_glfw_opengl3 PRIVATE imgui glfw opengl32.lib glu32.lib winmm.lib)
set_target_properties(example_glfw_opengl3 PROPERTIES FOLDER "Deps/imgui")
endif()

if(NOT DEFINED TP_implot OR TP_implot)
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

add_executable(implot_demo ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/implot_demo.cpp ${CMAKE_CURRENT_SOURCE_DIR}/implot/implot/main.cpp)
target_link_libraries(implot_demo PRIVATE imgui implot glfw opengl32.lib glu32.lib winmm.lib)

set_target_properties(implot PROPERTIES FOLDER "Deps/implot")
set_target_properties(implot_demo PROPERTIES FOLDER "Deps/implot")
endif()

if(NOT DEFINED TP_pugixml OR TP_pugixml)
############################ pugixml ############################
file(GLOB px_inc ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/pugixml/src/*.hpp)
file(GLOB px_src ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/pugixml/src/*.cpp)
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/pugixml/pugixml/src PREFIX pugixml FILES ${px_inc})

add_library(pugixml STATIC ${px_inc} ${px_src})
target_include_directories(pugixml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pugixml)
target_link_libraries(pugixml)
set_target_properties(pugixml PROPERTIES FOLDER "Deps/pugixml")
if(MSVC)
	target_compile_options(pugixml PRIVATE /W1 /WX)
else()
	target_compile_options(pugixml PRIVATE -Werror)
endif()
endif()


############################ Assimp ############################
#set(BUILD_SHARED_LIBS false CACHE BOOL "" FORCE)
#set(ASSIMP_INSTALL false CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_TESTS false CACHE BOOL "" FORCE)
#add_subdirectory(assimp)
#set_target_properties(assimp PROPERTIES FOLDER "Deps/assimp")
#set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER "Deps/assimp")
#set_target_properties(zlibstatic PROPERTIES FOLDER "Deps/assimp")

if(NOT DEFINED TP_openfbx OR TP_openfbx)
############################ openfbx ############################
file(GLOB of_inc ${CMAKE_CURRENT_SOURCE_DIR}/openfbx/openfbx/src/*.h)
file(GLOB of_src ${CMAKE_CURRENT_SOURCE_DIR}/openfbx/openfbx/src/*.c*)
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/openfbx/openfbx/src PREFIX openfbx FILES ${of_inc})
add_library(openfbx STATIC ${of_inc} ${of_src})
target_include_directories(openfbx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/openfbx)
target_link_libraries(openfbx)
set_target_properties(openfbx PROPERTIES FOLDER "Deps/openfbx")

target_compile_definitions(openfbx PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(openfbx PRIVATE /W1 /WX)
else()
	target_compile_options(openfbx PRIVATE -Werror)
endif()
endif()

if(NOT DEFINED TP_ufbx OR TP_ufbx)
############################ ufbx ############################
add_library(ufbx STATIC ${CMAKE_CURRENT_SOURCE_DIR}/ufbx/ufbx/ufbx.h ${CMAKE_CURRENT_SOURCE_DIR}/ufbx/ufbx/ufbx.c)
target_include_directories(ufbx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ufbx)
target_link_libraries(ufbx)
set_target_properties(ufbx PROPERTIES FOLDER "Deps/ufbx")

target_compile_definitions(ufbx PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(ufbx PRIVATE /W2 /WX)
else()
	target_compile_options(ufbx PRIVATE -Werror)
endif()
endif()

