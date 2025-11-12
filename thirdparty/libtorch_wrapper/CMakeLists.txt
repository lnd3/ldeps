
include(ExternalProject)

#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu121/libtorch-win-shared-with-deps-2.1.0%2Bcu121.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.1.0cu121)
#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu121/libtorch-win-shared-with-deps-2.1.2%2Bcu121.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.1.2cu121)
#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu121/libtorch-win-shared-with-deps-2.2.2%2Bcu121.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.2.2cu121)
#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu121/libtorch-win-shared-with-deps-2.3.1%2Bcu121.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.3.1cu121)
#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu121/libtorch-win-shared-with-deps-2.4.1%2Bcu121.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.4.1cu121)
#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu121/libtorch-win-shared-with-deps-2.5.1%2Bcu121.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.5.1cu121)

#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu124/libtorch-win-shared-with-deps-2.4.1%2Bcu124.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.4.1cu124)
#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu124/libtorch-win-shared-with-deps-2.5.1%2Bcu124.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.5.1cu124)
#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu124/libtorch-win-shared-with-deps-2.6.0%2Bcu124.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.6.0cu124)

#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu128/libtorch-win-shared-with-deps-2.8.0%2Bcu128.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.8cu128)

#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu129/libtorch-win-shared-with-deps-2.8.0%2Bcu129.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.8.0cu129)


#set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu130/libtorch-win-shared-with-deps-2.9.0%2Bcu130.zip")
#set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.9.0cu130)
set(LIBTORCH_URL "https://download.pytorch.org/libtorch/cu130/libtorch-win-shared-with-deps-2.9.1%2Bcu130.zip")
set(LIBTORCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libtorch2.9.1cu130)

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

if (TARGET libtorch_download)
    set(CAFFE2_USE_CUDNN ON CACHE INTERNAL "Caffe2 use cuDNN")
    find_package(Torch QUIET PATHS "${LIBTORCH_DIR}")

    #set(USE_CUDNN 1 CACHE INTERNAL "Use cuDNN")
    #set(CUDNN_FOUND TRUE CACHE INTERNAL "cuDNN found")

    if(TORCH_FOUND AND CUDNN_FOUND AND CUDA_FOUND)
        message(STATUS "Torch install prefix: ${TORCH_INSTALL_PREFIX}")
    	message(STATUS "Torch root: ${LIBTORCH_DIR}")
    	message(STATUS "Torch includes: ${TORCH_INCLUDE_DIRS}")
    	message(STATUS "Torch libs: ${TORCH_LIBRARIES}")

    	message(STATUS "Cuda root: ${CUDAToolkit_ROOT}")
    	message(STATUS "Cuda include: ${CUDA_INCLUDE_DIRS}")
    	message(STATUS "Cuda libs: ${CUDA_LIBRARIES}")

    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

        # Path to libtorch include/lib
        set(LIBTORCH_INCLUDE_DIR ${LIBTORCH_DIR}/include)
        set(LIBTORCH_LIB_DIR ${LIBTORCH_DIR}/lib)

        # Set these only after the project is built
        add_library(libtorch_wrapper STATIC ${CMAKE_CURRENT_SOURCE_DIR}/source/dummy.cpp)
        add_dependencies(libtorch_wrapper libtorch_download)

        target_include_directories(libtorch_wrapper PUBLIC 
            ${TORCH_INCLUDE_DIRS}
            ${LIBTORCH_INCLUDE_DIR}/torch/csrc/api/include        
            ${CUDA_INCLUDE_DIRS}
        )

        #target_link_directories(libtorch_wrapper PUBLIC ${LIBTORCH_LIB_DIR} ${CUDA_LIBRARIES})
        target_link_libraries(libtorch_wrapper PUBLIC
            "${LIBTORCH_LIB_DIR}/c10.lib"
            "${LIBTORCH_LIB_DIR}/c10_cuda.lib"
            "${LIBTORCH_LIB_DIR}/caffe2_nvrtc.lib"
            "${LIBTORCH_LIB_DIR}/cpuinfo.lib"
            "${LIBTORCH_LIB_DIR}/kineto.lib"
            "${LIBTORCH_LIB_DIR}/libprotobuf.lib"
            "${LIBTORCH_LIB_DIR}/libprotobuf-lite.lib"
            "${LIBTORCH_LIB_DIR}/libprotoc.lib"
            "${LIBTORCH_LIB_DIR}/pthreadpool.lib"
            "${LIBTORCH_LIB_DIR}/torch.lib"
            "${LIBTORCH_LIB_DIR}/torch_cpu.lib"
            "${LIBTORCH_LIB_DIR}/torch_cuda.lib"
            "${LIBTORCH_LIB_DIR}/XNNPACK.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn64_9.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn_cnn64_9.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn_ops64_9.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn_graph64_9.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn_heuristic64_9.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn_engines_precompiled64_9.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn_engines_runtime_compiled64_9.lib"
            "${CUDAToolkit_ROOT}/lib/x64/cudnn_adv64_9.lib"
            
        )
        target_compile_definitions(libtorch_wrapper PUBLIC LDEPS_USE_LIBTORCH=1)
        target_compile_features(libtorch_wrapper PUBLIC cxx_std_17)
        set(LDEPS_LIBTORCH_LIB_DIR ${LIBTORCH_LIB_DIR} CACHE INTERNAL "List of libtorch shared libraries")

        #file(WRITE ${LIBTORCH_DIR}/libtorch_stub.cpp "// Torch stub")
        #target_sources(libtorch PUBLIC ${LIBTORCH_DIR}/libtorch_stub.cpp)
        set_target_properties(libtorch_wrapper PROPERTIES FOLDER "Deps/thirdparty/libtorch")

    else()
    	message(WARNING "Libtorch not found. Disabling torch support.")
    	set(USE_LIBTORCH OFF)
    endif()
endif()