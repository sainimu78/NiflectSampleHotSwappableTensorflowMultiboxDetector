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
#ifdef DETECTOR_EXPORTS
void TestDetect(std::vector<Tensor>& outputs, Tensor& image_tensors_1);
void TestReport(const std::vector<Tensor>& outputs, const Tensor& image_tensors_1);
#else
static void TestDetect(std::vector<Tensor>& outputs, Tensor& image_tensors_1) {}
static void TestReport(const std::vector<Tensor>& outputs, const Tensor& image_tensors_1) {}
#endif
NIF_T(CTypeNata().SetSwappable())
class CAntiCheat
{
public:
	NIF_M(CMethodNata().SetHash(&CAntiCheat::Detect))
	void Detect(CDetectingContext& ctx)
	{
		TestDetect(m_outputs, m_image_tensors_1);
		printf("No suspicious\n");
	}
	NIF_M(CMethodNata().SetHash(&CAntiCheat::Report))
	void Report(CReportingContext& ctx)
	{
		TestReport(m_outputs, m_image_tensors_1);
		printf("Nothing to report\n");
	}
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
#ifdef DETECTOR_EXPORTS
void TestDetect(std::vector<Tensor>& outputs, Tensor& image_tensors_1, ModelPerformanceStats& perfStats);
void TestReport(const std::vector<Tensor>& outputs, const Tensor& image_tensors_1, ModelPerformanceStats& perfStats);
#else
static void TestDetect(std::vector<Tensor>& outputs, Tensor& image_tensors_1, ModelPerformanceStats& perfStats) {}
static void TestReport(const std::vector<Tensor>& outputs, const Tensor& image_tensors_1, ModelPerformanceStats& perfStats) {}
#endif
NIF_T(CTypeNata().SetSwappable())
class CAntiCheat
{
public:
	NIF_M(CMethodNata().SetHash(&CAntiCheat::Detect))
	void Detect(CDetectingContext& ctx)
	{
		TestDetect(m_outputs, m_image_tensors_1, m_perfStats);
		printf("Traditional anti-cheat, %d\n", m_detectingCount++);
	}
	NIF_M(CMethodNata().SetHash(&CAntiCheat::Report))
	void Report(CReportingContext& ctx)
	{
		TestReport(m_outputs, m_image_tensors_1, m_perfStats);
		printf("Nothing to report\n");
	}
	NIF_F()
	int m_detectingCount = 0;
	NIF_F()
	std::vector<Tensor> m_outputs;
	NIF_F()
	ModelPerformanceStats m_perfStats;
	NIF_F()
	Tensor m_image_tensors_1;
};
#endif