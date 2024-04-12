#pragma once

#include <SparrowEngine/SparrowEngine.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <list>

namespace RoboPioneers::Prometheus
{
	/**
	 * @brief 图像裁剪服务
	 * @author Vincent
	 * @details
	 *  ~ 该服务用于按照要求裁剪图像。
	 */
	class PictureCuttingService : public Sparrow::Service
	{
	public:
		struct {
			/**
			 * @brief 裁剪区域
			 * @details
			 *  ~ 若只有单项，采取兴趣区裁剪方式
			 *  ~ 若有多项，采取蒙版裁剪方式
			 */
			cv::Rect* CuttingAreas {nullptr};
		}Input;

		struct {
			/// 裁剪区域坐标偏移量（仅兴趣区方式有效）
			cv::Point CuttingAreaPositionOffset {0, 0};

			cv::cuda::GpuMat Result;
		}Output;

		/// 设定
		struct {
			bool DebugMode {false};
		}Settings;

	protected:
		/// 更新方法
		void OnUpdate(const Sparrow::Frame &frame) override;

	public:
		/**
		 * @brief 裁剪兴趣区域
		 * @param area 区域
		 * @return 裁剪结果
		 */
		static cv::cuda::GpuMat CutPictureByInterestedRegion(cv::cuda::GpuMat const * picture, cv::Rect area);
	};
}