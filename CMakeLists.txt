cmake_minimum_required(VERSION 3.19)


project(x64rdbg VERSION 1.1.2)

# reference: https://medium.com/3yourmind/generate-grpc-source-files-using-cmake-ec3acd246b45

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)


file(GLOB PROTO_FILES proto/*.proto)
file(GLOB PLUGIN_SRC_FILES src/*.cpp src/wrapper/*.cpp)


add_library(proto_objects OBJECT ${PROTO_FILES})

target_link_libraries(proto_objects
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
)

target_include_directories(proto_objects PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}")
set(PROTO_OUT_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)


protobuf_generate(
    TARGET proto_objects
    OUT_VAR PROTO_GENERATED_FILES
    LANGUAGE cpp
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR ${PROTO_OUT_DIR}
)
set_source_files_properties(${PROTO_GENERATED_FILES} PROPERTIES SKIP_UNITY_BUILD_INCLUSION on)


protobuf_generate(
    TARGET proto_objects
    OUT_VAR PROTO_GENERATED_FILES
    LANGUAGE grpc
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR ${PROTO_OUT_DIR}
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)
set_source_files_properties(${PROTO_GENERATED_FILES} PROPERTIES SKIP_UNITY_BUILD_INCLUSION on)


add_subdirectory(src/sdk)
configure_file(${PROJECT_SOURCE_DIR}/src/pluginconfig.h.in ${PROJECT_SOURCE_DIR}/src/pluginconfig.h)
x64dbg_plugin(x64rdbg ${PLUGIN_SRC_FILES})

target_include_directories(x64rdbg PRIVATE src)

target_link_libraries(x64rdbg
    PRIVATE
        proto_objects
)
