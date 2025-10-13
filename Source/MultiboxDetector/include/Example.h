#pragma once
#include "Niflect/Component/DefaultMacroTag.h"
#include "tensorflow/core/framework/tensor.h"

NIF_T()
class CHelloWorld
{
public:
	NIF_F()
	float m_value = 0.0f;
	NIF_F()
	tensorflow::Tensor m_tensor;
};