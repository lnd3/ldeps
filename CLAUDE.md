# ldeps project

## What This Is
`ldeps` is a collection of thirdparty C++ libraries.

## Content
- **bs**: Package `bs`. Location `./thirdparty/bs`. Main build system for cmake. Provides a structured layer on top of cmake to simplify project management and dependencies.
- **Curl**: Package `libcurl`. Location `./thirdparty/curl`.
- **mongoose**: Package `mongoose`. Location `./thirdparty/mongoose`. Network server for simple web services or testing.
- **PortAudio**: Package `portaudio`. Location `./thirdparty/portaudio/portaudio`. Audio library.
- **pthreads**: Package `pthreads`. Location `./src/pthreads`.
- **various**: Package `various`. Location `./src/various`. For example a tiny generalized serializer `serializer/Serializer.h` and a very efficient and easy-to-use json parser `jsmn.h`.
- **jsonxx**: Package `jsonxx`. Location `./thirdparty/jsonxx/jsonxx`. JSON parsing library used by the serialization layer.
- **pugixml**: Package `pugixml`. Location `./thirdparty_mods/pugixml/pugixml`. XML parsing library.

### Machine Learning Libraries
- **PyTorch C++**: Packages `libtorch_wrapper` and `libtorch_download`. Location `./thirdparty/libtorch_wrapper`. Download once then use the wrapper. PyTorch C++ is an advanced machine learning library.
- **Darknet**: Package `darknet`. Location `./thirdparty/darknet`. Image processing ai.
- **FANN**: Package `fann_static`. Location `./thirdparty/fann`. A Fast Artificial Neural Network.
- **NCNN**: Package `ncnn`. Location `./thirdparty/ncnn`. Advanced ML model.
- **tengine**: Package `tengine`. Location `./thirdparty/tengine`. Ai model.
- **Tiny DNN**: Package `tiny_dnn_static`. Location `./thirdparty/tiny-dnn`. Ai model.

### Crypto Libraries
- **cryptopp**: Package `cryptopp`. Location `./thirdparty_mods/cryptopp/cryptopp`.
- **ed25519**: Package `ed25519`. Location `./thirdparty/ed25519/ed25519`.
- **secp256k1**: Package `secp256k1`. Location `./thirdparty/secp256k1/secp256k1`.
- **micro-ecc**: Package `micro-ecc`. Location `./thirdparty/micro-ecc/micro-ecc`.
- **keccak**: Package `keccak`. Location `./thirdparty/keccak/keccak`. Cryptographic hashing.

### Graphics Libraries
- **glad**: Package `glad`. Location `./src/glad`.
- **bc7enc**: Package `bc7enc`. Location `./thirdparty_mods/bc7enc`. Png/bc7 encoder/decoder.
- **glfw**: Package `glfw`. Location `./thirdparty_mods/glfw`.
- **imgui**: Package `imgui`. Location `./thirdparty_mods/imgui/imgui`.
- **implot**: Package `implot`. Location `./thirdparty_mods/implot/implot`.
- **openfbx**: Package `openfbx`. Location `./thirdparty_mods/openfbx/openfbx`. FBX file format library.
- **ufbx**: Package `ufbx`. Location `./thirdparty_mods/ufbx/ufbx`. FBX file format library.
