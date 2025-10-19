#pragma once
#include "HotSwap/Nata.h"
#include "HotSwap/TypeSafeInvocationBestPractice.h"
#include <map>
#include "tensorflow/core/framework/tensor.h"
#include "Detector_gen.h"

NIF_T()
class CDetectingContext : public CInvocationContext
{
};

NIF_T()
class CReportingContext : public CInvocationContext
{
};

using namespace tensorflow;

#define RUNTIME_VERSION 0

#if RUNTIME_VERSION == 0
NIF_T(CTypeNata().SetSwappable())
class CDetector
{
public:
	NIF_M(CMethodNata().SetHash(&CDetector::Detect))
	void Detect(CDetectingContext& ctx);
	NIF_M(CMethodNata().SetHash(&CDetector::Report))
	void Report(CReportingContext& ctx);
	NIF_F()
	std::vector<Tensor> m_outputs;
	NIF_F()
	Tensor m_image_tensors_1;
};
#elif RUNTIME_VERSION == 1
// AI模型性能统计结构
NIF_T()
struct ModelPerformanceStats
{
	NIF_F() float inference_time = 0.0f;           // 推理时间(ms)
	NIF_F() float avg_confidence = 0.0f;           // 平均检测置信度
	NIF_F() int objects_detected = 0;              // 检测到的对象数量
	NIF_F() int high_confidence_detections = 0;    // 高置信度检测数量
	NIF_F() float detection_coverage = 0.0f;       // 检测覆盖率(检测框面积/图像面积)
	NIF_F() int total_detections = 0;              // 总检测次数
};
NIF_T(CTypeNata().SetSwappable())
class CDetector
{
public:
	NIF_M(CMethodNata().SetHash(&CDetector::Detect))
	void Detect(CDetectingContext& ctx);
	NIF_M(CMethodNata().SetHash(&CDetector::Report))
	void Report(CReportingContext& ctx);
	NIF_F()
	int m_detectedCount = 0;
	NIF_F()
	std::vector<Tensor> m_outputs;
	NIF_F()
	ModelPerformanceStats m_perfStats;
	NIF_F()
	Tensor m_image_tensors_1;
};
#endif