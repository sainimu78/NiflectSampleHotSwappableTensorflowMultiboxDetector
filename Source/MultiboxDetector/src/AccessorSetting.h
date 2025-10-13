#pragma once
#include "Niflect/Component/RwTree/Accessor/StandardRwAccessorSetting.h"
#include "tensorflow/core/framework/tensor.h"
#include "MySerialization.h"

namespace RwTree
{
	class CSSSSSSSSS : public CRwAccessor
	{
	public:
		virtual bool SaveImpl(Niflect::CNiflectType* type, const Niflect::InstanceType* base, CRwNode* rw) const override
		{
			auto& instance = *static_cast<const tensorflow::Tensor*>(base);
			auto rwValue = rw->ToValue();
			auto data = SerializeTensorToBinary(instance);
			rwValue->SetRawData(data.data(), data.size());
			return true;
		}
		virtual bool LoadImpl(Niflect::CNiflectType* type, Niflect::InstanceType* base, const CRwNode* rw) const override
		{
			auto& instance = *static_cast<tensorflow::Tensor*>(base);
			auto rwValue = rw->GetValue();
			auto& data = rwValue->GetRawData();
			std::string str;
			str.resize(data.size());
			memcpy(str.data(), data.data(), str.size());
			instance = DeserializeTensorFromBinary(str);
			return true;
		}
	};
}

namespace MyRwAccessorSetting
{
	using namespace NiflectAccessorSetting;
	using namespace RwTree;

	NIFAS_A() TSetting<RwTree::CSSSSSSSSS, tensorflow::Tensor>;
}