
include(ExternalProject)

option(USE_LIBTORCH_CUDA "Enable CUDA support for libtorch (requires CUDA toolkit and cuDNN)" OFF)

if(USE_LIBTORCH_CUDA)
    if(WIN32)
        set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu130/libtorch-win-shared-with-deps-2.9.1%2Bcu130.zip")
    else()
        set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu130/libtorch-shared-with-deps-2.9.1%2Bcu130.zip")
    endif()
    set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.9.1cu130)
else()
    if(WIN32)
        set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-2.9.1%2Bcpu.zip")
    else()
        set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-2.9.1%2Bcpu.zip")
    endif()
    set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.9.1cpu)
endif()

message(STATUS "Libtorch downloading to ${LIBTORCH_DIR}")

ExternalProject_Add(libtorch_download
    PREFIX ${CMAKE_BINARY_DIR}/libtorch_ep
    URL "${LIBTORCH_URL}"
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

if (TARGET libtorch_download)
    find_package(Torch QUIET PATHS "${LIBTORCH_DIR}")

    if(USE_LIBTORCH_CUDA)
        set(LIBTORCH_READY TORCH_FOUND AND CUDNN_FOUND AND CUDA_FOUND)
    else()
        set(LIBTORCH_READY TORCH_FOUND)
    endif()

    if(${LIBTORCH_READY})
        message(STATUS "Torch install prefix: ${TORCH_INSTALL_PREFIX}")
    	message(STATUS "Torch root: ${LIBTORCH_DIR}")
    	message(STATUS "Torch includes: ${TORCH_INCLUDE_DIRS}")
    	message(STATUS "Torch libs: ${TORCH_LIBRARIES}")

    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

        set(LIBTORCH_INCLUDE_DIR ${LIBTORCH_DIR}/include)
        set(LIBTORCH_LIB_DIR ${LIBTORCH_DIR}/lib)

        add_library(libtorch_wrapper STATIC ${CMAKE_CURRENT_SOURCE_DIR}/source/dummy.cpp)
        add_dependencies(libtorch_wrapper libtorch_download)

        target_include_directories(libtorch_wrapper PUBLIC
            ${TORCH_INCLUDE_DIRS}
            ${LIBTORCH_INCLUDE_DIR}/torch/csrc/api/include
        )

        if(WIN32)
            target_link_libraries(libtorch_wrapper PUBLIC
                "${LIBTORCH_LIB_DIR}/c10.lib"
                "${LIBTORCH_LIB_DIR}/cpuinfo.lib"
                "${LIBTORCH_LIB_DIR}/kineto.lib"
                "${LIBTORCH_LIB_DIR}/libprotobuf.lib"
                "${LIBTORCH_LIB_DIR}/libprotobuf-lite.lib"
                "${LIBTORCH_LIB_DIR}/libprotoc.lib"
                "${LIBTORCH_LIB_DIR}/pthreadpool.lib"
                "${LIBTORCH_LIB_DIR}/torch.lib"
                "${LIBTORCH_LIB_DIR}/torch_cpu.lib"
                "${LIBTORCH_LIB_DIR}/XNNPACK.lib"
            )
            if(USE_LIBTORCH_CUDA)
                target_include_directories(libtorch_wrapper PUBLIC ${CUDA_INCLUDE_DIRS})
                target_link_libraries(libtorch_wrapper PUBLIC
                    "${LIBTORCH_LIB_DIR}/c10_cuda.lib"
                    "${LIBTORCH_LIB_DIR}/caffe2_nvrtc.lib"
                    "${LIBTORCH_LIB_DIR}/torch_cuda.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn64_9.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn_cnn64_9.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn_ops64_9.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn_graph64_9.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn_heuristic64_9.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn_engines_precompiled64_9.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn_engines_runtime_compiled64_9.lib"
                    "${CUDAToolkit_ROOT}/lib/x64/cudnn_adv64_9.lib"
                )
            endif()
        else()
            target_link_libraries(libtorch_wrapper PUBLIC
                "${LIBTORCH_LIB_DIR}/libc10.so"
                "${LIBTORCH_LIB_DIR}/libcpuinfo.a"
                "${LIBTORCH_LIB_DIR}/libkineto.a"
                "${LIBTORCH_LIB_DIR}/libprotobuf.a"
                "${LIBTORCH_LIB_DIR}/libprotobuf-lite.a"
                "${LIBTORCH_LIB_DIR}/libprotoc.a"
                "${LIBTORCH_LIB_DIR}/libpthreadpool.a"
                "${LIBTORCH_LIB_DIR}/libtorch.so"
                "${LIBTORCH_LIB_DIR}/libtorch_cpu.so"
                "${LIBTORCH_LIB_DIR}/libXNNPACK.a"
            )
            if(USE_LIBTORCH_CUDA)
                target_include_directories(libtorch_wrapper PUBLIC ${CUDA_INCLUDE_DIRS})
                target_link_libraries(libtorch_wrapper PUBLIC
                    "${LIBTORCH_LIB_DIR}/libc10_cuda.so"
                    "${LIBTORCH_LIB_DIR}/libcaffe2_nvrtc.so"
                    "${LIBTORCH_LIB_DIR}/libtorch_cuda.so"
                )
            endif()
        endif()

        target_compile_definitions(libtorch_wrapper PUBLIC LDEPS_USE_LIBTORCH=1)
        target_compile_features(libtorch_wrapper PUBLIC cxx_std_17)
        set(LDEPS_LIBTORCH_LIB_DIR ${LIBTORCH_LIB_DIR} CACHE INTERNAL "List of libtorch shared libraries")
        set_target_properties(libtorch_wrapper PROPERTIES FOLDER "Deps/thirdparty/libtorch")

        if(USE_LIBTORCH_CUDA)
            message(STATUS "Cuda root: ${CUDAToolkit_ROOT}")
            message(STATUS "Cuda include: ${CUDA_INCLUDE_DIRS}")
            message(STATUS "Cuda libs: ${CUDA_LIBRARIES}")
        endif()
    else()
    	message(WARNING "Libtorch not found. Disabling torch support. (Re-run cmake after first build to find downloaded libtorch)")
    	set(USE_LIBTORCH OFF)
    endif()
endif()
