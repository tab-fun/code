#pragma once
#include "MenuData.h"
namespace M2
{
	class MenuDataSourceInterface
	{
	public:
		virtual CMenuData LoadMenuData() = 0;
	};
}
