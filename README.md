# NiflectSampleHotSwappableTensorflowMultiboxDetector

![Field_Level_Hot-Swapping_for_Live_TensorFlow_Model_Replacement](Doc/Field_Level_Hot-Swapping_for_Live_TensorFlow_Model_Replacement.gif)

## 演示工作流

本示例旨在演示模拟实际应用中一定会遇到的情况, 即因模型调整必须相应调整 C++ 侧字段.

通过本示例提出的 C++ 字段级热替换方法, 实现不重开应用替换模型并保持历史检测结果, 且执行效率达原生级.

本示例中, 图像检测部分的代码或资源移植自 TensorFlow 官方示例 tensorflow/examples/label_image 与 tensorflow/examples/multibox_detector

### 版本 0

使用的模型为 label_image 中的图像分类模型, 用于模拟某种不合期望的检测实现

#### 录屏中与版本 0 相关的步骤说明

1. 运行 MultiboxDetector
2. 输入 h, 加载版本 0 的 `CDetector`
3. 输入 d, 调用 `Detect`, 检测结果保存到 `m_outputs`
4. 输入 r, 调用 `Report`, 将 `m_outputs` 保存为图片 nihao.png
   - 此时可观察到检测蓝框处于错误的位置

### 版本 1

使用的模型为 multibox_detector 中的物体检测模型, 用于模拟一种期望的检测实现

#### 录屏中与版本 1 相关的步骤说明

1. 修改代码为版本 1 的 `CDetector`
2. 输入 h, 热替换 `CDetector` 实例
3. 输入 r, 调用 `Report`, 将版本 0 的结果 `m_outputs` 保存为图片
   - 此时可观察到由于版本 0 结果不符合版本 1 `Report` 的逻辑而产生更多位置错误的检测蓝框
   - 另可观察到模型性能评估打印输出中的指标不正常
4. 输入 d, 调用 `Detect` 检测结果保存到 `m_outputs`
5. 输入 r, 调用 `Report`, 将 `m_outputs` 保存为图片 nihao.png
   - 此时可观察到检测蓝框处于正确的位置
   - 另可观察到模型性能评估打印输出中的指标正常