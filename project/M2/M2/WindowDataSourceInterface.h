#pragma once
#include "WindowData.h"
namespace M2
{
	class CWindowData;
	// ʵ�ָýӿ�Ϊ�����ṩ����
	class WindowDataSourceInterface
	{
	public:
		virtual CWindowData LoadWindowData() = 0;
	};
}


