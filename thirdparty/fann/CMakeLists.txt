
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY TRUE CACHE BOOL "Skip install dependencies")
#set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries")
set(BUILD_SHARED_LIBS OFF)
set(BUILD_GMOCK False)

add_subdirectory(fann)
