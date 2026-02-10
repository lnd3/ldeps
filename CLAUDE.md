# ldeps project

## What This Is
`ldeps` is a collection of thirdparty c++ libraries.

## Content
- **bs**: Package `bs`. Location `deps/ldeps/thirdparty/bs`. Main build system for cmake. Provides a structured layer on top of cmake to simplify project management and dependencies.
- **Curl**: Package `libcurl`. Location `deps/ldeps/thirdparty/curl`.
- **mongoose**: Package `mongoose`. Location `deps/ldeps/thirdparty/mongoose`. Network server for simple web services or testing.
- **PortAudio**: Package `portaudio`. Location `deps/ldeps/thirdparty/portaudio/portaudio`. Audio library.
- **pthreads**: Package `pthreads`. Location `deps/ldeps/src/pthreads`.
- **various**: Package `various`. Location `deps/ldeps/src/various`. For example a tiny generalized serializer `serializer/Serializer.h` and a very efficient and easy-to-use json parser `jsmn.h`.

### Machine Learning Libraries
- **PyTorch C++**: Packages `libtorch_wrapper` and `libtorch_download`. Location `deps/ldeps/thirdparty/libtorch_wrapper`. Download once then use the wrapper. PyTorch C++ is an advanced machine learning library.
- **Darknet**: Package `darknet`. Location `deps/ldeps/thirdparty/darknet`. Image processing ai.
- **FANN**: Package `fann_static`. Location `deps/ldeps/thirdparty/fann`. A Fast Artificial Neural Network.
- **NCNN**: Package `ncnn`. Location `deps/ldeps/thirdparty/ncnn`. Advanced ML model.
- **tengine**: Package `tengine`. Location `deps/ldeps/thirdparty/tengine`. Ai model.
- **Tiny DNN**: Package `tiny_dnn_static`. Location `deps/ldeps/thirdparty/tiny-dnn`. Ai model.

### Crypto Libraries
- **cryptopp**: Package `cryptopp`. Location `deps/ldeps/thirdparty_mods/cryptopp/cryptopp`.
- **ed25519**: Package `ed25519`. Location `deps/ldeps/thirdparty/ed25519/ed25519`.
- **secp256k1**: Package `secp256k1`. Location `deps/ldeps/thirdparty/secp256k1/secp256k1`.
- **micro-ecc**: Package `micro-ecc`. Location `deps/ldeps/thirdparty/micro-ecc/micro-ecc`.

### Graphics Libraries
- **glad**: Package `glad`. Location `deps/ldeps/src/glad`.
- **bc7enc**: Package `bc7enc`. Location `deps/ldeps/thirdparty_mods/bc7enc`. Png/bc7 encoder/decoder.
- **glfw**: Package `glfw`. Location `deps/ldeps/thirdparty_mods/glfw`.
- **imgui**: Package `imgui`. Location `deps/ldeps/thirdparty_mods/imgui/imgui`.
- **implot**: Package `implot`. Location `deps/ldeps/thirdparty_mods/implot/implot`.

