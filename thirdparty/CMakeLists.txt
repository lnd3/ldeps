if(NOT DEFINED deps_bs OR deps_bs)
add_custom_target(bs SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/bs/cmake/bs.cmake)
set_target_properties(bs PROPERTIES FOLDER "Deps/thirdparty/bs")
endif()


if(NOT DEFINED deps_jsonxx OR deps_jsonxx)
############################ jsonxx ############################
file(GLOB_RECURSE jsonxx_inc ${CMAKE_CURRENT_SOURCE_DIR}/jsonxx/jsonxx/jsonxx.h)
file(GLOB_RECURSE jsonxx_src ${CMAKE_CURRENT_SOURCE_DIR}/jsonxx/jsonxx/jsonxx.cc)

add_library(jsonxx STATIC ${jsonxx_inc} ${jsonxx_src})
target_include_directories(jsonxx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/jsonxx)
set_target_properties(jsonxx PROPERTIES FOLDER "Deps/thirdparty/jsonxx")

target_compile_definitions(jsonxx PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(jsonxx PRIVATE /W1)
else()
	target_compile_options(jsonxx PRIVATE -Werror)
endif()
endif()


if(NOT DEFINED deps_curl OR deps_curl)
############################ CURL ############################
set(BUILD_SHARED_LIBS False)
set(BUILD_STATIC_LIBS True)
set(BUILD_TESTING False)
#set(CURL_CA_FALLBACK On)
set(CURL_ENABLE_SSL True)
set(ENABLE_WEBSOCKETS True)
set(BUILD_EXAMPLES False)

if(WIN32)
	set(CURL_USE_SCHANNEL True)
	set(CURL_WINDOWS_SSPI True)
	set(USE_WIN32_LDAP True)
endif()

set(CURL_USE_LIBPSL False)
set(PERL_EXECUTABLE False)
set(BUILD_LIBCURL_DOCS False)
#set(ENABLE_CURL_DEBUG On)
#set(ENABLE_DEBUG On)
#set(ENABLE_UNIX_SOCKETS On)

add_subdirectory(curl)
set_target_properties(curl PROPERTIES FOLDER "Deps/thirdparty/curl")

if(TARGET curl_uninstall)
	set_target_properties(curl_uninstall PROPERTIES FOLDER "Deps/thirdparty/curl")
endif()
if(TARGET libcurl_static)
	set_target_properties(libcurl_static PROPERTIES FOLDER "Deps/thirdparty/curl")
endif()
if(TARGET libcurl_object)
	set_target_properties(libcurl_object PROPERTIES FOLDER "Deps/thirdparty/curl")
	target_compile_definitions(libcurl_object PUBLIC CURL_ENABLE_SSL USE_WINDOWS_SSPI USE_SCHANNEL)
endif()
if(TARGET curltool)
	set_target_properties(curltool PROPERTIES FOLDER "Deps/thirdparty/curl")
endif()
if(TARGET curlinfo)
	set_target_properties(curlinfo PROPERTIES FOLDER "Deps/thirdparty/curl")
endif()

endif()


if(NOT DEFINED deps_mongoose OR deps_mongoose)
############################ Mongoose ############################
add_library(mongoose STATIC mongoose/mongoose/mongoose.h mongoose/mongoose/mongoose.c)
target_include_directories(mongoose PUBLIC mongoose)
set_target_properties(mongoose PROPERTIES FOLDER "Deps/thirdparty/mongoose")

target_compile_definitions(mongoose PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(mongoose PRIVATE /W0)
else()
	target_compile_options(mongoose PRIVATE -Werror -Wno-stringop-overread)
endif()
endif()


if(NOT DEFINED deps_portaudio OR deps_portaudio)
############################ Mongoose ############################

set(PA_BUILD_EXAMPLES False)

add_subdirectory(portaudio/portaudio)
set_target_properties(PortAudio PROPERTIES FOLDER "Deps/thirdparty/portaudio")
set_target_properties(uninstall PROPERTIES FOLDER "Deps/thirdparty/portaudio")

if(PA_BUILD_EXAMPLES)
set_target_properties(pa_devs PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(pa_fuzz PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_ocean_shore PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_pink PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_read_write_wire PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_record PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_record_file PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_saw PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_sine PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_wmme_ac3 PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_wmme_surround PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_write_sine PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_write_sine_nonint PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
set_target_properties(paex_sine_c++ PROPERTIES FOLDER "Deps/thirdparty/portaudio/examples")
endif()

target_compile_definitions(PortAudio PUBLIC cxx_std_14)
if(MSVC)
	target_compile_options(PortAudio PRIVATE /W3)
else()
	target_compile_options(PortAudio PRIVATE -w)
endif()
endif()


if(NOT DEFINED deps_ed25519 OR deps_ed25519)
############################ deps_ed25519 ############################
file(GLOB_RECURSE ed25519_inc ${CMAKE_CURRENT_SOURCE_DIR}/ed25519/ed25519/src/*.h)
file(GLOB_RECURSE ed25519_src ${CMAKE_CURRENT_SOURCE_DIR}/ed25519/ed25519/src/*.c)
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/ed25519/ed25519/src PREFIX ed25519 FILES ${ed25519_inc})

add_library(ed25519 STATIC ${ed25519_inc} ${ed25519_src})
target_include_directories(ed25519 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ed25519)
set_target_properties(ed25519 PROPERTIES FOLDER "Deps/thirdparty/ed25519")

if(MSVC)
	target_compile_options(ed25519 PRIVATE /W1)
else()
	target_compile_options(ed25519 PRIVATE -Werror -Wno-unused-result)
endif()
endif()


if(NOT DEFINED deps_darknet OR deps_darknet)
############################ deps_darknet ############################

# Disable CUDA for CPU-only
set(USE_CUDA OFF CACHE BOOL "Disable CUDA for CPU-only build")

# Glob Darknet headers and sources
file(GLOB darknet_inc ${CMAKE_CURRENT_SOURCE_DIR}/darknet/darknet/include/*.h)
file(GLOB darknet_src ${CMAKE_CURRENT_SOURCE_DIR}/darknet/darknet/src/*.*)
#SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}/darknet/darknet/include PREFIX darknet FILES ${darknet_inc})

add_library(darknet STATIC ${darknet_inc} ${darknet_src})
target_include_directories(darknet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/darknet/darknet/include)
target_link_libraries(darknet PUBLIC pthreads)

set_target_properties(darknet PROPERTIES FOLDER "Deps/thirdparty/darknet")

# Add examples
if(deps_darknet_examples)
add_executable(darknet_example_darknet ${CMAKE_CURRENT_SOURCE_DIR}/darknet/darknet/examples/darknet.c)
target_link_libraries(darknet_example_darknet PRIVATE pthreads darknet)
set_target_properties(darknet_example_darknet PROPERTIES FOLDER "Deps/thirdparty/darknet/examples")
add_executable(darknet_example_dice ${CMAKE_CURRENT_SOURCE_DIR}/darknet/darknet/examples/dice.c)
target_link_libraries(darknet_example_dice PRIVATE pthreads darknet)
set_target_properties(darknet_example_dice PROPERTIES FOLDER "Deps/thirdparty/darknet/examples")
add_executable(darknet_example_detector ${CMAKE_CURRENT_SOURCE_DIR}/darknet/darknet/examples/detector.c)
target_link_libraries(darknet_example_detector PRIVATE pthreads darknet)
set_target_properties(darknet_example_detector PROPERTIES FOLDER "Deps/thirdparty/darknet/examples")
endif()

target_compile_definitions(darknet PUBLIC cxx_std_17)
if(MSVC)
	target_compile_options(darknet PRIVATE /W3)
else()
	target_compile_options(darknet PRIVATE -w)
endif()
endif()


if(NOT DEFINED deps_tiny_dnn OR deps_tiny_dnn)
############################ deps_tiny_dnn ############################
add_subdirectory(tiny-dnn EXCLUDE_FROM_ALL)
set_target_properties(tiny_dnn PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")

endif()


if(NOT DEFINED deps_fann OR deps_fann)
############################ deps_tiny_dnn ############################

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE CACHE BOOL "Skip install dependencies")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")
set(BUILD_GMOCK False)

add_subdirectory(fann/fann)

set_target_properties(doublefann PROPERTIES FOLDER "Deps/thirdparty/fann")
set_target_properties(doublefann_static PROPERTIES FOLDER "Deps/thirdparty/fann")
set_target_properties(fann_static PROPERTIES FOLDER "Deps/thirdparty/fann")
set_target_properties(fann PROPERTIES FOLDER "Deps/thirdparty/fann")
#set_target_properties(fann_tests PROPERTIES FOLDER "Deps/thirdparty/fann")
set_target_properties(fixedfann PROPERTIES FOLDER "Deps/thirdparty/fann")
set_target_properties(fixedfann_static PROPERTIES FOLDER "Deps/thirdparty/fann")
set_target_properties(floatfann PROPERTIES FOLDER "Deps/thirdparty/fann")
set_target_properties(floatfann_static PROPERTIES FOLDER "Deps/thirdparty/fann")

endif()


if(NOT DEFINED deps_tengine OR deps_tengine)
############################ deps_tiny_dnn ############################

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE CACHE BOOL "Skip install dependencies")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")

if(deps_tengine_examples)
set(TENGINE_BUILD_BENCHMARK True)
set(TENGINE_BUILD_EXAMPLES True)
set(TENGINE_BUILD_DEMO True)
set(TENGINE_BUILD_TESTS True)
else()
set(TENGINE_BUILD_BENCHMARK False)
set(TENGINE_BUILD_EXAMPLES False)
set(TENGINE_BUILD_DEMO False)
set(TENGINE_BUILD_TESTS False)
endif()

set(TENGINE_BUILD_CPP_API False)

set(TENGINE_BUILD_CONVERT_TOOL False)
set(TENGINE_BUILD_QUANT_TOOL False)

set(TENGINE_OPENMP True)

set(TENGINE_ARCH_X86_AVX False)
set(TENGINE_ARCH_ARM_82 False)

set(TENGINE_STANDALONE_HCL False)
set(TENGINE_STANDALONE_HCL_AUTO_LOAD False)

set(TENGINE_ENABLE_ACL False)
set(TENGINE_ENABLE_CUDA False)
set(TENGINE_ENABLE_OPENCL False)
set(TENGINE_ENABLE_OPENDLA False)
set(TENGINE_ENABLE_TENSORRT False)
set(TENGINE_ENABLE_TIM_VX False)
set(TENGINE_ENABLE_TORCH False)
set(TENGINE_ENABLE_NNIE False)
set(TENGINE_ENABLE_VULKAN False)

set(TENGINE_DEBUG_DATA False)
set(TENGINE_DEBUG_TIME False)
set(TENGINE_DEBUG_MEM_STAT False)
set(TENGINE_ENABLE_ALL_SYMBOL False)

set(TENGINE_ENABLE_MODEL_CACHE False)

set(TENGINE_ONLINE_REPORT False)


add_subdirectory(tengine/tengine)

set_target_properties(tengine PROPERTIES FOLDER "Deps/thirdparty/tengine")
#target_compile_definitions(tengine PRIVATE TENGINE_ENABLE_OPENCL=0 TENGINE_ENABLE_CUDA=0) # CPU-only

endif()


if(NOT DEFINED deps_ncnn OR deps_ncnn)
############################ deps_tiny_dnn ############################

set(NCNN_SHARED_LIB False)
set(NCNN_ENABLE_LTO False)
set(NCNN_OPENMP True)
set(NCNN_STDIO True)
set(NCNN_STRING True)
set(NCNN_INSTALL_SDK False)
set(NCNN_SIMPLEOCV False)
set(NCNN_SIMPLEOMP False)
set(NCNN_SIMPLESTL False)
set(NCNN_SIMPLEMATH False)
set(NCNN_THREADS True)
set(NCNN_C_API True)
set(NCNN_PLATFORM_API True)
set(NCNN_PIXEL True)
set(NCNN_PIXEL_ROTATE True)
set(NCNN_PIXEL_AFFINE True)
set(NCNN_PIXEL_DRAWING True)
set(NCNN_CMAKE_VERBOSE False)
set(NCNN_VULKAN False)
set(NCNN_SIMPLEVK True)
set(NCNN_SYSTEM_GLSLANG True)
set(NCNN_RUNTIME_CPU True)
set(NCNN_DISABLE_PIC False)
set(NCNN_COVERAGE False)
set(NCNN_ASAN False)

if(deps_ncnn_examples)
set(NCNN_BENCHMARK True)
set(NCNN_BUILD_TESTS True)
set(NCNN_BUILD_BENCHMARK True)
else()
set(NCNN_BENCHMARK False)
set(NCNN_BUILD_TESTS False)
set(NCNN_BUILD_BENCHMARK False)
endif()

set(NCNN_PYTHON False)
set(NCNN_INT8 True)
set(NCNN_BF16 True)
set(NCNN_FORCE_INLINE True)

add_subdirectory(ncnn/ncnn)

set_target_properties(ncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn-generate-spirv PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(benchncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(darknet2ncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(mxnet2ncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn2int8 PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn2table PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn2mem PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnnmerge PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnnoptimize PROPERTIES FOLDER "Deps/thirdparty/ncnn")
#set_target_properties(ncnntestutil PROPERTIES FOLDER "Deps/thirdparty/ncnn")

endif()

