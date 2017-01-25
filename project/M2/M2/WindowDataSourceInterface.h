#pragma once
#include "WindowData.h"
namespace M2
{
	class CWindowData;
	// 实现该接口为窗口提供数据
	class WindowDataSourceInterface
	{
	public:
		virtual CWindowData LoadWindowData() = 0;
	};
}


