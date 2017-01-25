#pragma once
#include "Data.h"
namespace M2
{
	struct MenuItemInterface
	{
		virtual CMenuData LoadMenuItemData() = 0;
	};
}