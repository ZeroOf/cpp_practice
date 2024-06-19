# introduce

all is my demo code

## 3rd_party install

### boost

- `./b2 install --prefix=/home/will/3rd_party hardcode-dll-paths=true dll-path="/home/will/3rd_party/lib"`

### protobuf

- `cmake -B build -DCMAKE_CXX_STANDARD=14 -DCMAKE_INSTALL_PREFIX=/home/will/3rd_party/ -Dprotobuf_BUILD_TESTS=OFF -Dprotobuf_BUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_RPATH="/home/will/3rd_party/lib" -DCMAKE_BUILD_TYPE=Release --fresh`
- `cmake --build build --parallel 16 --config Release --target install`