#include "Service.hpp"

namespace RoboPioneers::Sparrow
{
	/// 更新方法
	void Service::Update(const Frame &frame)
	{
		if (Enable)
		{
			OnUpdate(frame);
		}
	}
}