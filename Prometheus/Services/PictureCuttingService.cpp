#include "PictureCuttingService.hpp"

#include <utility>
#include "../Modules/CUDAUtility.hpp"
#include "../Modules/ImageDebugUtility.hpp"

namespace RoboPioneers::Prometheus
{
	/// 更新方法
	void PictureCuttingService::OnUpdate(const Sparrow::Frame &frame)
	{
		if (Input.CuttingAreas->area() > 0)
		{
			Output.Result = CutPictureByInterestedRegion(&frame.GpuPicture,
			                             *Input.CuttingAreas);
			Output.CuttingAreaPositionOffset = {(Input.CuttingAreas->x, Input.CuttingAreas->y)};
		}
		else
		{
			Output.Result = frame.GpuPicture;
			Output.CuttingAreaPositionOffset = {0,0};
		}

		if (Settings.DebugMode)
		{
			Modules::ImageDebugUtility::ShowGPUPicture("Cutting Picture", Output.Result);
		}
	}

	/// 使用兴趣区方式裁剪图像
	cv::cuda::GpuMat PictureCuttingService::CutPictureByInterestedRegion(cv::cuda::GpuMat const *picture, cv::Rect area)
	{
		cv::cuda::GpuMat target(area.height, area.width, picture->type());
		(*picture)(std::move(area)).copyTo(target);
		return target;
	}
}
