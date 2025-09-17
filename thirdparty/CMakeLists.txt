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
set_target_properties(jsonxx PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

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
set_target_properties(mongoose PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES)

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

set_target_properties(PortAudio PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED YES)
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
add_subdirectory(darknet)
set_target_properties(darknet PROPERTIES FOLDER "Deps/thirdparty/darknet")
endif()


if(NOT DEFINED deps_tiny_dnn OR deps_tiny_dnn)
############################ deps_tiny_dnn ############################
add_subdirectory(tiny-dnn)
set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")
set_target_properties(tiny_dnn_static PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

if(MSVC)
	target_compile_options(tiny_dnn_static PRIVATE /W3)
else()
	target_compile_options(tiny_dnn_static PRIVATE -Werror -Wno-conversion -Wno-unused-result)
endif()
endif()


if(NOT DEFINED deps_fann OR deps_fann)
############################ deps_fann ############################
add_subdirectory(fann)
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
add_subdirectory(tengine)
set_target_properties(tengine PROPERTIES FOLDER "Deps/thirdparty/tengine")
#target_compile_definitions(tengine PRIVATE TENGINE_ENABLE_OPENCL=0 TENGINE_ENABLE_CUDA=0) # CPU-only
endif()


if(NOT DEFINED deps_ncnn OR deps_ncnn)
############################ deps_tiny_dnn ############################
add_subdirectory(ncnn)
set_target_properties(ncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn-generate-spirv PROPERTIES FOLDER "Deps/thirdparty/ncnn")
#set_target_properties(benchncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(darknet2ncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(mxnet2ncnn PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn2int8 PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn2table PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnn2mem PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnnmerge PROPERTIES FOLDER "Deps/thirdparty/ncnn")
set_target_properties(ncnnoptimize PROPERTIES FOLDER "Deps/thirdparty/ncnn")
#set_target_properties(ncnntestutil PROPERTIES FOLDER "Deps/thirdparty/ncnn")

endif()

if(NOT DEFINED deps_libtorch OR deps_libtorch)
option(USE_LIBTORCH "Enable support for libtorch" OFF)
if(USE_LIBTORCH)
    include(ExternalProject)

    set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu128/libtorch-win-shared-with-deps-2.8.0%2Bcu128.zip")
    set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch)

    message(STATUS "Libtorch downloading to ${LIBTORCH_DIR}")

    ExternalProject_Add(libtorch_download
        PREFIX ${CMAKE_BINARY_DIR}/libtorch_ep
        URL ${LIBTORCH_URL}
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        DOWNLOAD_NAME libtorch.zip
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON
        LOG_INSTALL ON
        SOURCE_DIR ${LIBTORCH_DIR}
    )
    set_target_properties(libtorch_download PROPERTIES FOLDER "Deps/thirdparty/libtorch")

	find_package(Torch QUIET PATHS "${LIBTORCH_DIR}")
	if(TORCH_FOUND)
		message(STATUS "Libtorch found at ${LIBTORCH_DIR}")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

        # Path to libtorch include/lib
        set(LIBTORCH_INCLUDE_DIR ${LIBTORCH_DIR}/include)
        set(LIBTORCH_LIB_DIR ${LIBTORCH_DIR}/lib)

      	compile_definitions(LDEPS_USE_LIBTORCH=1)

        # Set these only after the project is built
        add_library(libtorch INTERFACE)
        add_dependencies(libtorch libtorch_download)

        target_include_directories(libtorch INTERFACE
            ${LIBTORCH_INCLUDE_DIR}
            ${LIBTORCH_INCLUDE_DIR}/torch/csrc/api/include
        )

        target_link_directories(libtorch INTERFACE ${LIBTORCH_LIB_DIR})
        target_link_libraries(libtorch INTERFACE
            torch
            torch_cpu
            c10
        )
        target_compile_features(libtorch INTERFACE cxx_std_17)

        file(WRITE ${LIBTORCH_DIR}/libtorch_stub.cpp "// Torch stub")
        target_sources(libtorch INTERFACE ${LIBTORCH_DIR}/libtorch_stub.cpp)

        set_target_properties(libtorch PROPERTIES FOLDER "Deps/thirdparty/libtorch")

	else()
		message(WARNING "Libtorch not found. Disabling torch support.")
		set(USE_LIBTORCH OFF)
	endif()

endif()
endif()

