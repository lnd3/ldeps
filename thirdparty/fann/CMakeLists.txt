
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE CACHE BOOL "Skip install dependencies")
#set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")
set(BUILD_SHARED_LIBS OFF)
set(BUILD_GMOCK False)

add_subdirectory(fann)

target_include_directories(doublefann PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)
target_include_directories(doublefann_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)
target_include_directories(fann PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)
target_include_directories(fann_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)
target_include_directories(fixedfann PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)
target_include_directories(fixedfann_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)
target_include_directories(floatfann PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)
target_include_directories(floatfann_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fann/src/include)

