
set(USE_SSE True)
set(USE_AVX True)
set(USE_AVX2 True)
set(USE_TBB False)
set(USE_OMP True)
set(USE_NNPACK False)
set(USE_CBLAS False)
set(USE_INTEL_MKL False)
set(USE_OPENCL False)
set(USE_LIBDNN False)
set(USE_SERIALIZER True)
set(USE_DOUBLE False)
set(USE_IMAGE_API True)
set(USE_GEMMLOWP True)

set(BUILD_TESTS False)
set(BUILD_EXAMPLES False)
set(BUILD_DOCS False)
set(BUILD_BENCHMARKS False)
set(COVERALLS False)
set(PROFILE False)
set(USE_ASAN False)

add_subdirectory(tiny-dnn)

add_library(tiny_dnn_static STATIC dummy.cpp)
target_link_libraries(tiny_dnn_static PUBLIC tiny_dnn)

set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")
set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")
set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")
set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")
set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")
set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")
set_target_properties(tiny_dnn_static PROPERTIES FOLDER "Deps/thirdparty/tiny_dnn")



