#pragma once
#include "tensorflow/core/framework/tensor.h"

using namespace tensorflow;

// ���л�Tensor���ַ���
static std::string SerializeTensorToString(const Tensor& tensor) {
    TensorProto tensor_proto;
    // ��Tensorת��ΪTensorProto
    tensor.AsProtoTensorContent(&tensor_proto);

    // ���л�Ϊ�ַ���
    std::string serialized_str;
    tensor_proto.SerializeToString(&serialized_str);
    return serialized_str;
}

// ���ַ��������л�Tensor
static Tensor DeserializeTensorFromString(const std::string& serialized_str) {
    TensorProto tensor_proto;
    tensor_proto.ParseFromString(serialized_str);

    Tensor tensor;
    // ��TensorProto�ָ�Tensor
    CHECK(tensor.FromProto(tensor_proto));
    return tensor;
}