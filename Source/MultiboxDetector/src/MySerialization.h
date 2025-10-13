#pragma once
#include "tensorflow/core/framework/tensor.h"

using namespace tensorflow;

// 序列化Tensor到字符串
static std::string SerializeTensorToString(const Tensor& tensor) {
    TensorProto tensor_proto;
    // 将Tensor转换为TensorProto
    tensor.AsProtoTensorContent(&tensor_proto);

    // 序列化为字符串
    std::string serialized_str;
    tensor_proto.SerializeToString(&serialized_str);
    return serialized_str;
}

// 从字符串反序列化Tensor
static Tensor DeserializeTensorFromString(const std::string& serialized_str) {
    TensorProto tensor_proto;
    tensor_proto.ParseFromString(serialized_str);

    Tensor tensor;
    // 从TensorProto恢复Tensor
    CHECK(tensor.FromProto(tensor_proto));
    return tensor;
}